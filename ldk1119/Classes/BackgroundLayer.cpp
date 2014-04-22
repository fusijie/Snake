#include "BackgroundLayer.h"


BackgroundLayer::BackgroundLayer(void)
{
}


BackgroundLayer::~BackgroundLayer(void)
{
}
bool BackgroundLayer::init(){
	if(!Layer::init())
		return false;
	//获取坐标
	Size  visibile=Director::getInstance()->getVisibleSize();
	Point  origin=Director::getInstance()->getVisibleOrigin();
	Sprite *background=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.jpg"));
	//设置锚点，坐标点，
	background->setAnchorPoint(Point::ZERO);
	background->setPosition(Point::ZERO);
	this->addChild(background);
	return true;
}