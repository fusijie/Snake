#include "MenuScene.h"

#include "GameScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init()
{

	if(!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	
	auto labelGameName = Label::create("Block Snake" , "" , 40);
	labelGameName->setAnchorPoint(Point(.5f , .5f));
	labelGameName->setPosition( visibleSize.width / 2 , visibleSize.height - 200);
	this->addChild(labelGameName);

	auto menuStartGame = MenuItemFont::create("StartGame" , 
		CC_CALLBACK_1(MenuScene::menuCloseCallback,this));
	menuStartGame->setTag(1);
	menuStartGame->setPosition( visibleSize.width / 2 , visibleSize.height / 2 );

	auto menuExitGame = MenuItemFont::create("ExitGame" , 
		CC_CALLBACK_1(MenuScene::menuCloseCallback,this));
	menuExitGame->setTag(2);
	menuExitGame->setPosition( visibleSize.width / 2 , visibleSize.height / 2 - 50 );

	int lastScore = UserDefault::getInstance()->getIntegerForKey("score" , -1);
	if(lastScore > 0){
		auto labelScore = Label::create(String::createWithFormat("High Score: %d" , lastScore)->getCString() , "" , 25);
		labelScore->setAnchorPoint(Point(.5f , .5f));
		labelScore->setPosition( visibleSize.width / 2 , 200);
		this->addChild(labelScore);
	}

	auto menu = Menu::create(menuStartGame , menuExitGame , NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	return true;
}

void MenuScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	auto menuItem = (MenuItem*)pSender;
	switch (menuItem->getTag())
	{
	case 1:
		{
			menuItem->setEnabled(false);
			auto gameScene = GameScene::createScene();
			Director::getInstance()->replaceScene(gameScene);
			break;
		}
	case 2:
		{
			Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif
		}
	default:
		break;
	}
}