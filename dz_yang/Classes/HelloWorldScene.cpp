#include "HelloWorldScene.h"

USING_NS_CC;

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
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    auto listener1 = EventListenerTouchOneByOne::create();//创建一个监听
    listener1->setSwallowTouches(true);//设置是否想下传递触摸
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());//获取的当前触摸的目标
        
        Point p = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        auto winsize = Director::getInstance()->getVisibleSize();
        
        auto th_is = static_cast<HelloWorld*>(event->getCurrentTarget());
        
        if (rect.containsPoint(p))//判断触摸点是否在目标的范围内
        {
            if(winsize.height/winsize.width * p.x+p.y>winsize.height)
            {
                if(winsize.height/winsize.width * p.x<p.y && th_is->direction!=3)
                {
                    log("up");
                    th_is->reSch();
                    th_is->move(1, th_is->snake.size()-1);
                }else if(winsize.height/winsize.width * p.x>p.y && th_is->direction!=4)
                {
                    log("left");
                    th_is->reSch();
                    th_is->move(2, th_is->snake.size()-1);
                }
            }else
            {
                if(winsize.height/winsize.width * p.x<p.y && th_is->direction!=2)
                {
                    log("right");
                    th_is->reSch();
                    th_is->move(4, th_is->snake.size()-1);
                }
                else if(winsize.height/winsize.width * p.x>p.y && th_is->direction!=1)
                {
                    log("down");
                    th_is->reSch();
                    th_is->move(3, th_is->snake.size()-1);
                }
            }
            
            return true;
        }else
            return false;  
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    this->apple = Sprite::create("bo.png");
    apple->setAnchorPoint(Point(0,0));
    apple->setPosition(Point(22*20,12*20));
    apple->setColor(Color3B(255,0,0));
    this->addChild(this->apple);
    
    
    auto head = Sprite::create("bo.png");
    head->setAnchorPoint(Point(0,0));
    head->setPosition(Point(2*20,12*20));
    head->setColor(Color3B(0,255,0));
    this->snake.pushBack(head);
    this->addChild(this->snake.at(0));
    
    this->direction = 2;
    this->speed = 100;
    schedule(schedule_selector(HelloWorld::up_date), 60/this->speed);
    
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::up_date(float dt){
    move(this->direction, this->snake.size()-1);
}

void HelloWorld::move(int direction, int snake_ind){
    this->direction = direction;
    if (snake_ind == 0) {
        auto pos = snake.at(0)->getPosition();
        switch (direction) {
            case 1:this->snake.at(0)->setPosition(Point(pos.x,pos.y+20));
                break;
            case 2:this->snake.at(0)->setPosition(Point(pos.x+20,pos.y));
                break;
            case 3:this->snake.at(0)->setPosition(Point(pos.x,pos.y-20));
                break;
            case 4:this->snake.at(0)->setPosition(Point(pos.x-20,pos.y));
                break;
            default:
                break;
        }
        this->testEat();
    }else if(snake_ind >0 && snake_ind <= 50){
        this->snake.at(snake_ind)->setPosition(( snake.at(snake_ind-1)->getPosition()));
        move(direction, snake_ind-1);
    }
    testGameisOver(true);
    
}

void HelloWorld::testGameisOver(bool b){
    auto winsize = Director::getInstance()->getVisibleSize();
    if (b) {
        //失败情况 1.撞墙 2.吃到自己 （移动后检测）
        
        bool b = false;
        if (snake.size()>2) {
            for (auto i=1; i<this->snake.size(); i++) {
                auto body_size = this->snake.at(i)->getContentSize();
                auto body_point = this->snake.at(i)->getPosition();
                auto body_rect = Rect(body_point.x,body_point.y,20 ,20);
                auto head_point = this->snake.at(0)->getPosition();
                auto app = Point(head_point.x+10,head_point.y+10);
                if(body_rect.containsPoint(app)){
                    b=true;
                }
            }
        }
        
        if (this->snake.at(0)->getPositionX() >= winsize.width || this->snake.at(0)->getPositionX() < 0 ||
            this->snake.at(0)->getPositionY() >= winsize.height || this->snake.at(0)->getPositionY() < 0 || b)
        {
            //game over
            unschedule(schedule_selector(HelloWorld::up_date));
            _eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
            auto label = LabelTTF::create("GAME OVER", "Arial", 50);
            label->setPosition(Point(winsize.width/2,winsize.height/2));
            this->addChild(label, 1);
            label->setScale(0);
            label->runAction(ScaleTo::create(3, 1.5));
            label->setOpacity(0);
            label->runAction(FadeTo::create(1.5, 255));
            this->runAction(Sequence::create(DelayTime::create(5),CallFunc::create([]{Director::getInstance()->replaceScene(HelloWorld::createScene());}), NULL));
            
        }
        
    }else{
        //胜利情况 长度到达40 （吃东西后检测）
        if (this->snake.size() == 50) {
            //game win
            unschedule(schedule_selector(HelloWorld::up_date));
            _eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
            auto label = LabelTTF::create("U WIN", "Arial", 50);
            label->setPosition(Point(winsize.width/2,winsize.height/2));
            this->addChild(label, 1);
            label->setScale(0);
            label->runAction(ScaleTo::create(3, 1.5));
            label->setOpacity(0);
            label->runAction(FadeTo::create(1.5, 255));
            this->runAction(Sequence::create(DelayTime::create(5),CallFunc::create([]{Director::getInstance()->replaceScene(HelloWorld::createScene());}), NULL));
        }
        
    }
    
}

void HelloWorld::reSch(){
    unschedule(schedule_selector(HelloWorld::up_date));
    schedule(schedule_selector(HelloWorld::up_date), 60/this->speed);
    

}

void HelloWorld::testEat(){
    auto head_size = this->snake.at(0)->getContentSize();
    auto head_point = this->snake.at(0)->getPosition();
    auto head_rect = Rect(head_point.x,head_point.y,20 ,20);
    auto apple_point = this->apple->getPosition();
    auto ap = Point(apple_point.x+10,apple_point.y+10);
    if(head_rect.containsPoint(ap)){
        log("Good eat!!");
        
        auto body = Sprite::create("bo.png");
        body->setAnchorPoint(Point(0,0));
        body->setColor(Color3B(0,255,0));
        this->snake.pushBack(body);
        this->addChild(this->snake.at(this->snake.size()-1));
        body->setPosition(this->snake.at(this->snake.size()-2)->getPosition());
        
        //random set apple
        auto winsize = Director::getInstance()->getVisibleSize();
        auto x_l = winsize.width/20-1;
        auto y_l = winsize.height/20-1;
        while (true) {
            srand((int)time(NULL)+(int)time(0));
            this->apple->setPosition(Point( (rand() % ((int)x_l+1)) *20,(rand() % ((int)y_l+1))*20));
            bool b = true;
            for (auto i=0; i<this->snake.size(); i++) {
                auto body_size = this->snake.at(i)->getContentSize();
                auto body_point = this->snake.at(i)->getPosition();
                auto body_rect = Rect(body_point.x,body_point.y,20 ,20);
                auto apple_ppoint = this->apple->getPosition();
                auto app = Point(apple_ppoint.x+10,apple_ppoint.y+10);
                if(body_rect.containsPoint(app)){
                    b=false;
                }
            }
            if (b)
                break;
        }
        
        
        
        testGameisOver(false);
    }
}


void HelloWorld::draw(cocos2d::Renderer* renderer, const kmMat4 &transform, bool transformUpdated){
    //draw Line
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    glLineWidth(3);
    DrawPrimitives::setDrawColor4B(255, 255,0, 20);
    DrawPrimitives::drawLine(Point(0,0), Point(visibleSize.width,visibleSize.height));
    DrawPrimitives::drawLine(Point(0,visibleSize.height), Point(visibleSize.width, 0));
    CHECK_GL_ERROR_DEBUG();

}