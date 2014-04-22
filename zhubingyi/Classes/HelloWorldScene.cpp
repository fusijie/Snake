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
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //Point origin = Director::getInstance()->getVisibleOrigin();
    background = Sprite::create("StartScene.png");
    background->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(background);
    
    playbutton = MenuItemImage::create("PlayButton1.png","PlayButton2.png",CC_CALLBACK_0(HelloWorld::ChangeScene,this));
    playbutton ->setPosition(Point(visibleSize.width/2,visibleSize.height/2-1.5*playbutton->getContentSize().height));
    
    menu = Menu::create(playbutton,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    return true;
}

void HelloWorld::ChangeScene(){
    //log("Change");
    Director::getInstance()->replaceScene(TransitionProgressInOut::create(0.5f,GameLayer::GameScene()));
}


