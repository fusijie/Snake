//
//  GameHelp.cpp
//  Snake
//
//  Created by fireblackill on 14-4-10.
//
//

#include "GameHelp.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* GameHelp::createScene()
{
    auto scene = Scene::create();
    auto layer = GameHelp::create();
    scene->addChild(layer);
    return scene;
}

bool GameHelp::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    //创建帮助文字
    auto labelHelp = Label::create("Please click screen to start the game!", "宋体", 24);
    labelHelp->setPosition(Point(480,320));
    this->addChild(labelHelp);
    
    //创建返回按钮
    auto labelBack = Label::create("MainMenu", "宋体", 24);
    auto uiBack = MenuItemLabel::create(labelBack, CC_CALLBACK_1(GameHelp::menuBackToMain, this));
    uiBack->setPosition(Point(100,50));
    
    auto menu = Menu::create(uiBack,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    return true;
    
}

void GameHelp::menuBackToMain(cocos2d::Ref *pSender)
{
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}


