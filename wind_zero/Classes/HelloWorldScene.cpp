#include "HelloWorldScene.h"
#include "CCEventDispatcher.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	auto labelStart = Label::create("StartGame", "Arial", 24);
	auto labelHelp = Label::create("GameHelp", "Arial", 24);
	auto labelExit = Label::create("ExitGame", "Arial", 24);

	auto startItem = MenuItemLabel::create(labelStart, CC_CALLBACK_1(HelloWorld::menuCallback, this));
	startItem->setTag(START);
	startItem->setPosition(Point(100, 200));

	auto helpItem = MenuItemLabel::create(labelHelp, CC_CALLBACK_1(HelloWorld::menuCallback, this));
	helpItem->setTag(HELP);
	helpItem->setPosition(Point(100, 150));

	auto exitItem = MenuItemLabel::create(labelExit, CC_CALLBACK_1(HelloWorld::menuCallback, this));
	exitItem->setTag(EXIT);
	exitItem->setPosition(Point(100, 50));

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
	closeItem->setTag(EXIT);
    auto menu = Menu::create(startItem, helpItem, exitItem, closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    auto label = Label::create("Snake", "Arial", 24);
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    return true;
}


void HelloWorld::menuCallback(Ref* pSender)
{
	switch (((Node*)pSender)->getTag())
	{
	case START:
		CCLOG("go to game");
		Director::getInstance()->replaceScene(GameScene::createScene());
		break;
	case  HELP:
		CCLOG("go to help");
		Director::getInstance()->replaceScene(GameHelp::createScene());
		break;
	case EXIT:
		Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}
}

bool GameHelp::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto labelHelp = Label::create("please touch screen to play the game", "Arial", 15);
	labelHelp->setPosition(Point(visibleSize.width / 2, 280));
	labelHelp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	this->addChild(labelHelp);

	auto labelBack = Label::create("Main Menu", "Arial", 15);
	auto itemBack = MenuItemLabel::create(labelBack, CC_CALLBACK_1(GameHelp::menuBackToMain, this));
	itemBack->setPosition(Point(visibleSize.width / 2, 160));

	auto menu = Menu::create(itemBack, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	return true;
}

Scene* GameHelp::createScene()
{
	auto scene = Scene::create();
	auto layer = GameHelp::create();
	scene->addChild(layer);
	return scene;
}

void GameHelp::menuBackToMain( cocos2d::Ref* pSender )
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto labelBack = Label::create("Main Menu", "Arial", 15);
	auto itemBack = MenuItemLabel::create(labelBack, CC_CALLBACK_1(GameScene::menuBackToMain, this));
	itemBack->setPosition(Point(visibleSize.width, 0));
	itemBack->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);

	auto menu = Menu::create(itemBack, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	sHead = new SnakeNode();
	sHead->row = rand()%10;
	sHead->col = rand()%15;
	sHead->preNode = NULL;

	sFood = new SnakeNode();
	sFood->row = rand()%10;
	sFood->col = rand()%15;

	auto snakeNode = Sprite::create("node_snake.png");
	snakeNode->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	snakeNode->setPosition(Point(sHead->col * 32, sHead->row * 32));
	sHead->nodeSprite = snakeNode;
	this->addChild(snakeNode);

	auto foodNode = Sprite::create("node_food.png");
	foodNode->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	foodNode->setPosition(Point(sFood->col * 32, sFood->row * 32));
	sFood->nodeSprite = foodNode;
	this->addChild(foodNode);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	this->schedule(SEL_SCHEDULE(&GameScene::logic), 0.5f);
	return true;
}

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

void GameScene::menuBackToMain( cocos2d::Ref* pSender )
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

bool GameScene::onTouchBegan( Touch* touch, Event* event )
{
	Point touchPoint = touch->getLocation();
	int touchRow = ((int)touchPoint.y) / 32;
	int touchCol = ((int)touchPoint.x) / 32;

	if (abs(touchRow - sHead->row) > abs(touchCol - sHead->col))
	{
		if (touchRow > sHead->row)
		{
			sHead->dir = DIR_DEF::UP;
		} 
		else
		{
			sHead->dir = DIR_DEF::DOWN;
		}		
	}
	else
	{
		if (touchCol > sHead->col)
		{
			sHead->dir = DIR_DEF::RIGHT;
		} 
		else
		{
			sHead->dir = DIR_DEF::LEFT;
		}		
	}
	
	return true;
}

void GameScene::logic( float t )
{
	for (int i = allbody.size() - 1; i >= 0; i--)
	{
		auto sn = allbody.at(i);
		sn->dir = sn->preNode->dir;
		sn->row = sn->preNode->row;
		sn->col = sn->preNode->col;
		sn->nodeSprite->setPosition(Point(sn->col * 32, sn->row *32));
	}
	
	switch (sHead->dir)
	{
	case DIR_DEF::UP:
		sHead->row ++;
		if (sHead->row >= 10)
		{
			sHead->row = 0;
		}
		break;
	case DIR_DEF::DOWN:
		sHead->row --;
		if (sHead->row <= 0)
		{
			sHead->row = 9;
		}
		break;
	case DIR_DEF::LEFT:
		sHead->col --;
		if (sHead->col <= 0)
		{
			sHead->col = 14;
		}
		break;
	case DIR_DEF::RIGHT:
		sHead->col ++;
		if (sHead->col >= 15)
		{
			sHead->col = 0;
		}		
		break;
	}
	sHead->nodeSprite->setPosition(Point(sHead->col * 32, sHead->row * 32));

	if (sHead->col == sFood->col && sHead->row == sFood->row)
	{
		sFood->row = rand()%10;
		sFood->col = rand()%15;
		sFood->nodeSprite->setPosition(Point(sFood->col * 32, sFood->row * 32));
		auto snakeNode = new SnakeNode();
		if (allbody.empty())
		{
			snakeNode->preNode = sHead;
		}
		else
		{
			snakeNode->preNode = allbody.back();
		}
		switch (snakeNode->preNode->dir)
		{
		case DIR_DEF::UP:
			snakeNode->row = snakeNode->preNode->row - 1;
			snakeNode->col = snakeNode->preNode->col;
			break;
		case DIR_DEF::DOWN:
			snakeNode->row = snakeNode->preNode->row + 1;
			snakeNode->col = snakeNode->preNode->col;
			break;
		case DIR_DEF::LEFT:
			snakeNode->row = snakeNode->preNode->row;
			snakeNode->col = snakeNode->preNode->col + 1;
			break;
		case DIR_DEF::RIGHT:
			snakeNode->row = snakeNode->preNode->row;
			snakeNode->col = snakeNode->preNode->col - 1;
			break;
		}

		auto nodeSprite = Sprite::create("node_snake.png");
		nodeSprite->setPosition(Point(snakeNode->col * 32, snakeNode->row * 32));
		nodeSprite->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		snakeNode->nodeSprite = nodeSprite;
		this->addChild(nodeSprite);

		allbody.pushBack(snakeNode);
	}
	
}
