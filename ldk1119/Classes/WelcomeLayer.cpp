#include "WelcomeLayer.h"
#include "GameScene.h"


WelcomeLayer::WelcomeLayer(void)
{
}


WelcomeLayer::~WelcomeLayer(void)
{
}
bool WelcomeLayer::init(){
	if(!Layer::init())
		return false;
	Size visibleSize=Director::getInstance()->getVisibleSize();
	Point origin=Director::getInstance()->getVisibleOrigin();
	Sprite* background;
	background=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.jpg"));
	background->setAnchorPoint(Point::ZERO);
	background->setPosition(Point::ZERO);
	this->addChild(background);
	auto logo=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("snake_logo.png"));
	logo->setPosition(Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height*0.6f));
	this->addChild(logo);
	 //add the start-menu to the current sceneÌí¼ÓÒ»¸öButton
	Sprite *startButton = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("snake_play.png"));
	//Sprite *activeStartButton = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameCache()->getSpriteFrameByName("btn-play-selected.png"));
	//activeStartButton->setPositionY(5);
	auto menuItem  = MenuItemSprite::create(startButton,NULL,CC_CALLBACK_1(WelcomeLayer::menuStartCallback, this));
	menuItem->setPosition(Point(origin.x + visibleSize.width/2 ,origin.y + visibleSize.height*0.3f));

    auto menu = Menu::create(menuItem,NULL);
	menu->setPosition(Point(origin.x ,origin.y));
	this->addChild(menu,1);
	//__________________________________//

	return true;
}
void WelcomeLayer::menuStartCallback(Ref *sender){
	auto *scene=GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}