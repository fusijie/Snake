#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define BACKGROUND_SOUND "background.wav"
#define EAT_SOUND "effect.wav"
#define GAMEOVER_SOUND "gameover.wav"

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto labelStart = Label::createWithSystemFont("Start", "Arial", 32);
    
	auto startItem = MenuItemLabel::create(labelStart, CC_CALLBACK_1(HelloWorld::menuCallback, this));
	startItem->setTag(START);
	startItem->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height-420));

	auto menu = Menu::create(startItem,  NULL); 
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	auto label = Label::createWithSystemFont("Snake", "Arial", 64);
	label->setPosition(Point(visibleSize.width/2,
		visibleSize.height-160));
	this->addChild(label, 1);

    if(highScore>0){
        char buff[20] = {0};
        sprintf(buff,"High Score: %d",highScore);
        auto labelHighScore = Label::createWithSystemFont(buff, "Arial", 32);
        labelHighScore->setPosition(Point(visibleSize.width/2,
                                          visibleSize.height-320));
        this->addChild(labelHighScore);
    }
    
    Director::getInstance()->setDisplayStats(false);
	return true;
}


void HelloWorld::menuCallback(Ref* pSender)
{
	switch (((Node*)pSender)->getTag()) {
	case START:         
		CCLOG("go to game");
		Director::getInstance()->replaceScene(GameScene::createScene());
		break;     
	case EXIT:         
		Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)         
		exit(0); 
#endif 
	}
}

bool GameScene::init() 
{     
	if (!Layer::init())     {
		return false;     
	}       
	Size visibleSize = Director::getInstance()->getVisibleSize();       
	auto labelBack = Label::createWithSystemFont("Main Menu", "Arial", 16);
	auto itemBack = MenuItemLabel::create(labelBack, CC_CALLBACK_1(GameScene::menuBackToMain, this));     
	itemBack->setPosition(Point(visibleSize.width, 0));     
	itemBack->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);       
	auto menu = Menu::create(itemBack, NULL);     
	menu->setPosition(Point(0, 0));     
	this->addChild(menu);
    
    this->labelScore = Label::createWithSystemFont("Score: 0", "Arial", 22);
	this->labelScore->setPosition(Point(visibleSize.width- labelScore->getContentSize().width,
                             visibleSize.height - labelScore->getContentSize().height));
	this->addChild(labelScore);
    
    winWidth=visibleSize.width;
    winHeight=visibleSize.height;
    score=0;
	speed=0.1f;
    gameOverFlag=false;
    gameOverDelay=1.0f/speed;

    //初始化蛇
    snakeLength=3;
    snakeNodeWidth=18;
    snakeStep=1;
    snakeAllStep=0;
    controlDir=DIR_DEF::LEFT;
    int x=winWidth-snakeLength*snakeNodeWidth-10;
    int y=rand()%winHeight-snakeNodeWidth;
    x=(x/snakeNodeWidth)*snakeNodeWidth;
    y=(y/snakeNodeWidth)*snakeNodeWidth;
    

    for(int i=0;i<snakeLength;i++){
        auto sprite = Sprite::create("snake.png");
        auto node = new SnakeNode();
        node->x=x+snakeNodeWidth*i;
        node->y=y;
        int dir=controlDir;
        node->sprite=sprite;
        node->sprite->setPosition(Point(node->x, node->y));
        node->sprite->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        

        this->addChild(node->sprite);
        snake.pushBack(node);
        if(i>0){
            for(int j=0;j<snakeStep;j++){
                auto dirNode = new DirNode();
                dirNode->dir=dir;
                dirChain.pushBack(dirNode);
            }
        }
    }
    
    //初始化蛋
    egg =genEgg();
    this->addChild(egg->sprite);
    
    //建立触摸监听
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    //建立键盘监听
    auto listenerKeyboard = EventListenerKeyboard::create();
    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    listenerKeyboard->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BACKGROUND_SOUND);

    
    this->schedule(SEL_SCHEDULE(&GameScene::play), speed);
    
	return true; 
}

SnakeNode* GameScene::genEgg(){
    auto node=new SnakeNode();
    auto sprite = Sprite::create("egg.png");
    node->x=rand()%winWidth-sprite->getContentSize().width;
    node->y=rand()%winHeight-sprite->getContentSize().height;
    node->sprite=sprite;
    node->sprite->setPosition(Point(node->x, node->y));
    //node->sprite->setAnchorPoint(Point::ANCHOR_MIDDLE);
    node->sprite->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    return node;
}
bool GameScene::onTouchBegan( Touch* touch, Event* event )
{
    Point touchPoint = touch->getLocation();
    touch_x= (int)touchPoint.x;
    touch_y= (int)touchPoint.y;
    return true;
}
void GameScene::onTouchEnded( Touch* touch, Event* event )
{
    Point touchPoint = touch->getLocation();
    int x = (int)touchPoint.x;
    int y = (int)touchPoint.y;
    int x1=touch_x;
    int y1=touch_y;
    int dir;
    
    if (abs(y - y1) > abs(x - x1)) {
        if (y > y1) dir = DIR_DEF::UP;
        else dir = DIR_DEF::DOWN;
    }
    else {
        if (x > x1)
            dir = DIR_DEF::RIGHT;
        else dir = DIR_DEF::LEFT;
    }
    snakeMove(dir);
}


// Implementation of the keyboard event callback function prototype
void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d pressed", keyCode);
    
    if(keyCode==EventKeyboard::KeyCode::KEY_LEFT_ARROW) snakeMove(DIR_DEF::LEFT);
    else if(keyCode==EventKeyboard::KeyCode::KEY_UP_ARROW) snakeMove(DIR_DEF::UP);
    else if(keyCode==EventKeyboard::KeyCode::KEY_RIGHT_ARROW) snakeMove(DIR_DEF::RIGHT);
    else if(keyCode==EventKeyboard::KeyCode::KEY_DOWN_ARROW) snakeMove(DIR_DEF::DOWN);
    
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d released", keyCode);
}

void GameScene::snakeMove(int dir){
    //避免舌头直接撞到蛇身
    if(controlDir==DIR_DEF::UP && dir == DIR_DEF::DOWN);
    else if(controlDir==DIR_DEF::DOWN && dir == DIR_DEF::UP);
    else if(controlDir==DIR_DEF::LEFT && dir == DIR_DEF::RIGHT);
    else if(controlDir==DIR_DEF::RIGHT && dir == DIR_DEF::LEFT);
    else controlDir=dir;
}
void GameScene::play(float t)
{
    if(!gameOverFlag){
        //移动蛇
        for(int i=snake.size()-1;i>=0;i--){
            SnakeNode *node=snake.at(i);
            int x=node->x;
            int y=node->y;
            int d=controlDir;
            int step=snakeNodeWidth/snakeStep;
            if(i==0) d=controlDir;
            else {
                DirNode *dirNode =dirChain.at((i-1)*snakeStep+snakeStep-1);
                d=dirNode->dir;
                //CCLOG("end %d %d",dirChain.,y);
            }
            switch (d)
            {
                case DIR_DEF::UP:
                    y +=step;
                    break;
                case DIR_DEF::DOWN:
                    y -=step;
                    break;
                case DIR_DEF::LEFT:
                    x -=step;
                    break;
                case DIR_DEF::RIGHT:
                    x +=step;
                    break;
            }
            
            node->x=x;
            node->y=y;
            //node->sprite->setPosition(Point(node->x, node->y));
            
            float duration =speed*0.8f;//+(CCRANDOM_0_1()-0.5f)*speed*0.2 ;
            auto actionMove = MoveTo::create(duration,
                                             Point(node->x, node->y));
            
            node->sprite->runAction(Sequence::create(actionMove, NULL, NULL));
            
            
        }
        //调整移动方向链
        for(int i=dirChain.size()-1;i>=0;i--){
            DirNode *dirNode=dirChain.at(i);
            int d=dirNode->dir;
            if(i==0) d=controlDir;
            else {
                DirNode *lastDirNode =dirChain.at(i-1);
                d=lastDirNode->dir;
            }
            dirNode->dir=d;
        }
        
        //碰撞判断
        SnakeNode *head=snake.at(0);
        //检测是否吃到蛋
        if(collisionDetection(head,egg)){
            //处理并显示分数
            score+=1;//增加分数
            if(score>highScore) highScore=score;
            this->removeChild(labelScore);
            char buff[20] = {0};
            sprintf(buff,"Score: %d",score);
            labelScore = Label::createWithSystemFont(buff, "Arial", 22);
            
            labelScore->setPosition(Point(winWidth-labelScore->getContentSize().width,
                                          winHeight-labelScore->getContentSize().height));
            this->addChild(labelScore);
            
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EAT_SOUND);

            //增长蛇身的处理
            auto tail=snake.at(snake.size()-1);
            auto sprite = Sprite::create("snake.png");
            auto node = new SnakeNode();
            Point pt=tail->sprite->getPosition();
            node->x=tail->x;
            node->y=tail->y;
            node->sprite=sprite;
            node->sprite->setPosition(Point(node->x, node->y));
            node->sprite->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
            this->addChild(node->sprite);
            snake.pushBack(node);
            snakeLength++;
            
            for(int j=0;j<snakeStep;j++){
                auto dirNode = new DirNode();
                dirNode->dir=0;
                dirChain.pushBack(dirNode);
            }
            
            
            //生成新的鸡蛋
            this->removeChild(egg->sprite);
            egg =genEgg();
            this->addChild(egg->sprite);
            
        }
        else {
            //检测是否撞到边界
            if(borderDetection(head->sprite)) {
                gameOverFlag=true;
            }
            //检测是否撞到蛇身
            for(int i=2;i<snake.size();i++){
                SnakeNode *node=snake.at(i);
                if(collisionDetection(head,node)) {
                    gameOverFlag=true;
                    break;
                }
            }
        }
        snakeAllStep++;
        if(gameOverFlag){
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GAMEOVER_SOUND);
            double PI=3.14159f;
            
            for(int i=0;i<snake.size();i++){
                SnakeNode *node=snake.at(i);
                int dir;
                if(i==0) dir=controlDir;
                else {
                    DirNode *dirNode=dirChain.at((i-1)*snakeStep+snakeStep-1);
                    dir=dirNode->dir;
                }
                double angle=(rand()%150+15)*PI/180;
                if(dir==DIR_DEF::UP) angle=-angle;
                else if(dir==DIR_DEF::LEFT) angle=angle-PI/2;
                else if(dir==DIR_DEF::RIGHT) angle=angle+PI/2;

                int x=node->x+cos(angle)*snakeNodeWidth*100.0f;
                int y=node->y+sin(angle)*snakeNodeWidth*100.0f;
                //log("%d %d angle: %d %d,%d",node->x,node->y,(int)(angle/PI*180),x,y);
                float duration =speed*20.0f;//+(CCRANDOM_0_1()-0.5f)*speed*0.2 ;
                auto actionMove = MoveTo::create(duration,
                                                 Point(x, y));
                
                node->sprite->runAction(Sequence::create(actionMove, NULL, NULL));
            }

        }
    }
    else {
        gameOverDelay--;
        if(gameOverDelay<0) gameOver();
    }
}

void GameScene::gameOver(){
    CCLOG("Game Over");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();//停止全部音效
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

Scene* GameScene::createScene()
{
	auto scene = Scene::create();    
	auto layer = GameScene::create();     
	scene->addChild(layer);     
	return scene; 
}   

void GameScene::menuBackToMain( cocos2d::Ref* pSender ) {
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

bool GameScene::borderDetection(cocos2d::Sprite* sprite){
    Point pt=sprite->getPosition();
    Size sz=sprite->getContentSize();
    if(pt.x<0 || pt.y<0 || pt.x+sz.width>=winWidth || pt.y+sz.height>=winHeight) return true;
    else return false;
}

bool GameScene::collisionDetection(SnakeNode* node1,SnakeNode* node2){
    Size sz1=node1->sprite->getContentSize();
    int p1x1=node1->x;
    int p1y1=node1->y;
    int p1x2=p1x1+sz1.width-1;
    int p1y2=p1y1+sz1.height-1;
    Size sz2=node2->sprite->getContentSize();
    int p2x1=node2->x;
    int p2y1=node2->y;
    int p2x2=p2x1+sz2.width-1;
    int p2y2=p2y1+sz2.height-1;
    //CCLOG("%d %d %d %d - %d %d %d %d ",p1x1,p1x2,p1y1,p1y2,p2x1,p2x2,p2y1,p2y2);
    if(p1x1>p2x2 || p1x2<p2x1 || p1y1>p2y2 || p1y2<p2y1) return false;
    else return true;
}
