#include "StatusLayer.h"


StatusLayer::StatusLayer(void)
{
}


StatusLayer::~StatusLayer(void)
{
}
bool StatusLayer::init(){
	if(!Layer::init())
		return false;
	Size size=Director::getInstance()->getVisibleSize();
	Point origin=Director::getInstance()->getVisibleOrigin();
	statusSprite=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("getready.png"));
	statusSprite->setPosition(Point(origin.x+size.width/2,origin.y+size.height*0.6f));
	statusSprite->setScale(2.0f);
	this->addChild(statusSprite);
	
	return true;
}
void StatusLayer::onGameStart(){
	Size size=Director::getInstance()->getVisibleSize();
	Point origin=Director::getInstance()->getVisibleOrigin();
	statusSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("getready.png"));
	statusSprite->setVisible(true);

}
void StatusLayer::onGamePlay(){
	statusSprite->setVisible(false);
	

}
void StatusLayer::onGameEnd(){
	auto size=Director::getInstance()->getVisibleSize();
	auto origin=Director::getInstance()->getVisibleOrigin();
	statusSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("gameover.png"));
	statusSprite->setVisible(true);


}
