#include "HelloWorldScene.h"
#include "GameHelp.h"
#include "GameLayer.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
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

    //创建文字按钮
    auto labelStart = Label::create("Start Game", "宋体", 24);
    auto labelHelp = Label::create("Game Help", "宋体", 24);
    auto labelExit = Label::create("Exit Game", "宋体", 24);
    
    auto uiStart = MenuItemLabel::create(labelStart, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    uiStart->setTag(1);
    uiStart->setPosition(Point(100,200));
    
    auto uiHelp = MenuItemLabel::create(labelHelp, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    uiHelp->setTag(2);
    uiHelp->setPosition(Point(100,150));
    
    auto uiExit = MenuItemLabel::create(labelExit, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    uiExit->setTag(3);
    uiExit->setPosition(Point(100,50));
    
    auto menu = Menu::create(uiStart,uiHelp, uiExit, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    int i = dynamic_cast<Node*>(pSender)->getTag();
    switch (i)
    {
        case 1:
            log("go to Game");
            Director::getInstance()->replaceScene(GameLayer::createScene());
            break;
        case 2:
            log("go to Help");
            Director::getInstance()->replaceScene(GameHelp::createScene());
            break;
        case 3:
        case 4:
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
            break;
        default:
            break;
    }
    
}
