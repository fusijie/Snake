#include "GameScene.h"
#include "SnakeSprite.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* GameScene::createScene() {
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}


bool GameScene::init() {
	if(!Layer::init()){
		return false;
	}
	// 随机数因子
	srand((unsigned)time(NULL)); 
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image.plist");

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto layerMain = Layer::create();
	layerMain->setContentSize(Size(960 , 640));
	layerMain->ignoreAnchorPointForPosition(false);
	layerMain->setPosition( visibleSize.width / 2 , visibleSize.height / 2 );
	this->addChild(layerMain);

	// 游戏背景图（算什么背景图 不都是黑色么。）
	auto spriteBackground = Sprite::createWithSpriteFrameName("background.png");
	spriteBackground->setPosition( 480 , 320 );
	layerMain->addChild(spriteBackground);

	// 游戏地图
	layerGameMap = Layer::create();
	layerGameMap->setContentSize(Size( 760 , 560 ));
	layerGameMap->setAnchorPoint(Point(0 ,0));
	layerGameMap->setPosition( 100 , 19.5f );
	spriteBackground->addChild(layerGameMap);

	// 添加食物
	spriteFood = Sprite::createWithSpriteFrameName("food.png");
	spriteFood->setAnchorPoint(Point(0,0));
	layerGameMap->addChild(spriteFood);

	// 创建默认蛇头部
	spriteHeader = SnakeSprite::create("snake-head-up.png");
	spriteHeader->setTag(0);
	spriteHeader->setPosition( 40 , 0 );
	layerGameMap->addChild(spriteHeader , 2);

	// 给蛇添加个尾巴
	spriteFooter = SnakeSprite::create();
	spriteFooter->setPosition( 0 , 0 );
	spriteFooter->setTag(1);
	layerGameMap->addChild(spriteFooter);

	// 时间分数
	labelScore = Label::create("Score: 0" , "" , 40);
	labelScore->setAnchorPoint(Point( 0 , .5f ));
	labelScore->setPosition(Point( 100 , 610 ));
	layerMain->addChild(labelScore);

	labelTime = Label::create("Time: 00:00:00" , "" , 35);
	labelTime->setAnchorPoint(Point( 0 , .5f ));
	labelTime->setPosition(Point( 620 , 610 ));
	layerMain->addChild(labelTime);

	 // 各种菜单item初始化 代码恶心  请勿细看
	auto menuItemUp = MenuItemSprite::create(Sprite::createWithSpriteFrameName("up-normal.png") , 
		Sprite::createWithSpriteFrameName("up-press.png") , CC_CALLBACK_1(GameScene::menuCloseCallback,this));
	menuItemUp->setTag(UP);
	menuItemUp->setPosition( 50 , 80 );

	auto menuItemDown = MenuItemSprite::create(Sprite::createWithSpriteFrameName("down-normal.png") , 
		Sprite::createWithSpriteFrameName("down-press.png") , CC_CALLBACK_1(GameScene::menuCloseCallback,this));
	menuItemDown->setTag(DOWN);
	menuItemDown->setPosition( visibleSize.width - 50 , 80 );

	auto menuItemRight = MenuItemSprite::create(Sprite::createWithSpriteFrameName("right-normal.png") , 
		Sprite::createWithSpriteFrameName("right-press.png") , CC_CALLBACK_1(GameScene::menuCloseCallback,this));
	menuItemRight->setTag(RIGHT);
	menuItemRight->setPosition( visibleSize.width - 50 , 300 );

	auto menuItemLeft = MenuItemSprite::create(Sprite::createWithSpriteFrameName("left-normal.png") , 
		Sprite::createWithSpriteFrameName("left-press.png") , CC_CALLBACK_1(GameScene::menuCloseCallback,this));
	menuItemLeft->setTag(LEFT);
	menuItemLeft->setPosition( 50 , 300 );

	menuItemRestart = MenuItemFont::create("Restart" , CC_CALLBACK_1(GameScene::menuCloseCallback,this));
	menuItemRestart->setTag(RESTART);
	menuItemRestart->setVisible(false);
	menuItemRestart->setPosition( visibleSize.width / 2 , visibleSize.height / 2 );

	menuItemMenu = MenuItemFont::create("ReturnMenu" , CC_CALLBACK_1(GameScene::menuCloseCallback,this));
	menuItemMenu->setTag(MENU);
	menuItemMenu->setVisible(false);
	menuItemMenu->setPosition( visibleSize.width / 2 , visibleSize.height / 2 - 50 );

	auto menuMain = Menu::create(menuItemUp , menuItemDown , menuItemRight , menuItemLeft ,menuItemRestart ,menuItemMenu , NULL);
	menuMain->setPosition(Point::ZERO);
	this->addChild(menuMain);

	start();

	return true;
}

void GameScene::menuCloseCallback(cocos2d::Ref* pSender) {
	MenuItem* item = (MenuItem*)pSender;
	DIRECTION direction = (DIRECTION)item->getTag();
	switch (direction) {
	case UP:
	case DOWN:
	case RIGHT:
	case LEFT:
		changeDirection(direction);
		break;
	case RESTART:
		start();
		break;
	case MENU:
		{
			auto scene = MenuScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
		break;
	default:
		break;
	}
}

void GameScene::start() {
	menuItemRestart->setVisible(false);
	menuItemMenu->setVisible(false);
	for (int i = 2 ; i < bones ; i++) {
		layerGameMap->removeChildByTag(i);
	}
	gameScore = 0; // 分数
	bones = 2; //  头  尾
	gameTime = 0; // 时间
	labelTime->setString("Time: 00:00:00");
	labelScore->setString("Score: 0");
	isMoveEnd = false;
	currDirection = RIGHT;
	this->schedule(schedule_selector(GameScene::gameTask), UP_TIME);
	this->schedule(schedule_selector(GameScene::timeTask), 1.0f);
	createFood();
	spriteHeader->setSpriteFrame("snake-head-right.png");
	spriteHeader->setPosition( 40 , 0 );
	spriteFooter->setPosition( 0 , 0 );
}

void GameScene::gameTask(float t) {
	if(isMoveEnd){ return; };
	check();
	move();
}

void GameScene::end() {
	this->unschedule(schedule_selector(GameScene::gameTask));
	this->unschedule(schedule_selector(GameScene::timeTask));
	menuItemRestart->setVisible(true);
	menuItemMenu->setVisible(true);
	auto userData = UserDefault::getInstance();
	int lastScore = userData->getIntegerForKey("score" , 0);
	if(lastScore < gameScore){
		userData->setIntegerForKey("score" , gameScore);
		userData->flush();
	}
}

void GameScene::move() {
	isMoveEnd = true;
	for (int i = 0 ; i < bones ; i++) {
		auto snake = (SnakeSprite*)layerGameMap->getChildByTag(i);
		auto snakePoint = snake->getPosition();
		SnakeSprite* preSnake = NULL;
		Point preSnakePoint;
		if(i == 0) {
			Point snakeCurrPoint;
			switch (currDirection) {
			case RIGHT:
				snakeCurrPoint = snakePoint + CCPoint(40 , 0);
				break;
			case LEFT:
				snakeCurrPoint = snakePoint + CCPoint(-40 , 0);
				break;
			case DOWN:
				snakeCurrPoint = snakePoint + CCPoint(0 , -40);
				break;
			case UP:
				snakeCurrPoint = snakePoint + CCPoint(0 , 40);
				break;
			default:
				break;
			}

			if(snakeCurrPoint.x >= 760 || snakeCurrPoint.x < 0 || snakeCurrPoint.y >= 560 || snakeCurrPoint.y < 0) {
				end();
				return;
			}
			snake->setPosition(snakeCurrPoint);
			snake->setNextPoint(snakePoint);
		}  else  {
			preSnake = (SnakeSprite*)layerGameMap->getChildByTag(i - 1);
			preSnakePoint = preSnake->getNextPoint();

			snake->setPosition(preSnakePoint);
			snake->setNextPoint(snakePoint);
		}
	}
	isMoveEnd = false;
}

void GameScene::check() {
	// 如果头部跟实物坐标一致则代表吃了一个食物
	if(spriteFood->getPosition() == spriteHeader->getPosition()) {
		SimpleAudioEngine::getInstance()->playEffect("eat.wav");
		addBody();
		createFood();
		gameScore += 5;
		labelScore->setString(CCString::createWithFormat("Score: %d" , gameScore)->getCString());
	}

	// 检查当前头部是否与身体节点重叠  重叠为自己咬自己  游戏结束
	for (int i = 1 ; i < bones ; i++) {
		auto spriteSnake = (SnakeSprite*)layerGameMap->getChildByTag(i);
		if(spriteHeader->getPosition() == spriteSnake->getPosition()) {
			end();
		}
	}
}

void GameScene::addBody() {
	auto spriteBody = SnakeSprite::create();
	spriteBody->setTag(bones);
	layerGameMap->addChild(spriteBody);
	bones++;
}

void GameScene::createFood() {
	// 760 / 40       560 / 40
	int xNumder = (19 * CCRANDOM_0_1());
	int yNumder = (14 * CCRANDOM_0_1());
	Point pointFood = Point(xNumder * 40 , yNumder * 40);
	// 防止食物生成在蛇身体节点上
	for (int i = 0 ; i < bones ; i++) {
		auto spriteSnake = (SnakeSprite*)layerGameMap->getChildByTag(i);
		if(spriteSnake->getPosition() == pointFood) {
			createFood();
			return;
		}
	}
	spriteFood->setPosition( xNumder * 40 , yNumder * 40);
}

void GameScene::timeTask(float) {
	gameTime++;
	int shi,fen,miao;
	shi = gameTime / 3600;
	fen = gameTime / 60 % 60;
	miao = gameTime % 60;
	labelTime->setString(CCString::createWithFormat("Time: %02d:%02d:%02d" , shi , fen , miao)->getCString());
}

void GameScene::onEnter() {
	Layer::onEnter();
	SimpleAudioEngine::getInstance()->preloadEffect("eat.wav");

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan=CC_CALLBACK_2(GameScene::onTouchBegan , this);
	listener->onTouchEnded=CC_CALLBACK_2(GameScene::onTouchEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}

void GameScene::onExit() {
	Layer::onExit();
	SimpleAudioEngine::getInstance()->unloadEffect("eat.wav");
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
	if(layerGameMap->getBoundingBox().containsPoint(touch->getLocation())){
		return true;
	}
	return false;
}

void GameScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *unused_event) {
	Point pointStart = pTouch->getStartLocation();
	Point pointEnd = pTouch->getLocation();
	int x = pointStart.x - pointEnd.x;
	int y = pointStart.y - pointEnd.y;
	if(abs(x) > abs(y))  { 
		if(x + 100 > 0)  { 
			changeDirection(LEFT);
		}  else  { 
			changeDirection(RIGHT);
		}
	}  else {
		if(y + 100 > 0)  { 
			changeDirection(DOWN);
		}  else  { 
			changeDirection(UP);
		}
	}
}

void GameScene::changeDirection(DIRECTION direction) {
	switch (direction) {
	case UP:
		if( currDirection == UP || currDirection == DOWN ){ return; }
		spriteHeader->setSpriteFrame("snake-head-up.png");
		break;
	case DOWN:
		if( currDirection == UP || currDirection == DOWN ){ return; }
		spriteHeader->setSpriteFrame("snake-head-down.png");
		break;
	case RIGHT:
		if( currDirection == RIGHT || currDirection == LEFT ){ return; }
		spriteHeader->setSpriteFrame("snake-head-right.png");
		break;
	case LEFT:
		if( currDirection == RIGHT || currDirection == LEFT ){ return; }
		spriteHeader->setSpriteFrame("snake-head-left.png");
		break;
	}
	currDirection = direction;
}