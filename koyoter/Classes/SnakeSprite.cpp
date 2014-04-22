#include "SnakeSprite.h"

USING_NS_CC;

bool SnakeSprite::init()
{
	if(!Sprite::initWithSpriteFrameName("snake-body.png")){
		return false;
	}
	this->setAnchorPoint(Point::ZERO);
	return true;
}

SnakeSprite* SnakeSprite::create(const char* file)
{
	SnakeSprite* spriteSnake = new SnakeSprite;
	if(spriteSnake->initWithSpriteFrameName(file)){
		spriteSnake->setAnchorPoint(Point::ZERO);
		spriteSnake->autorelease();
		return spriteSnake;
	}
	CC_SAFE_RELEASE_NULL(spriteSnake);
	return NULL;
}

void SnakeSprite::setNextPoint(cocos2d::Point point)
{
	this->nextPoint = point;
} 
cocos2d::Point SnakeSprite::getNextPoint()
{
	return this->nextPoint;
}
