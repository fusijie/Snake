#include "GameHome.h"
#include "Game.h"

void GameHome::close(Ref* sender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameHome::onEnter()
{
	Scene::onEnter();

	createTitle();
	createMenu();
}

void GameHome::createMenu()
{
	auto menu = Menu::create(
		createMenuTTF("play",Point(0,30),CC_CALLBACK_1(GameHome::play,this)),
		createMenuTTF("close",Point(0,-100),CC_CALLBACK_1(GameHome::close,this)),
		nullptr);
	this->addChild(menu);
}

MenuItemLabel* GameHome::createMenuTTF( const std::string& name,const Point& pos,const ccMenuCallback& callback )
{
	auto closeLabel = Label::create(name,"fonts/Marker Felt.ttf",40);
	closeLabel->enableShadow(Color3B::GREEN);
	auto menuItemLabel = MenuItemLabel::create(closeLabel,callback);
	menuItemLabel->setPosition(pos);
	return menuItemLabel;
}

void GameHome::createTitle() // 创建一个标题
{
	auto title = Label::create("Greedy Snake","fonts/Marker Felt.ttf",50);
	title->setAnchorPoint(Point::ANCHOR_MIDDLE);
	title->setPosition(480,520);
	title->enableShadow(Color3B::RED);
	this->addChild(title);
}

void GameHome::play( Ref* sender )
{
	Director::getInstance()->replaceScene(Game::create());
}
