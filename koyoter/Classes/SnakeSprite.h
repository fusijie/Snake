#ifndef _SNAKESPRITE_SPRITE_H__
#define _SNAKESPRITE_SPRITE_H__

#include "cocos2d.h"

class SnakeSprite : public cocos2d::Sprite
{
public:
	virtual bool init();
	CREATE_FUNC(SnakeSprite);

	// 头部的图片不一样  所以有vip特权加个特别的函数
	static SnakeSprite* create(const char*);
	
	// 设置后面一个节点的坐标
	void setNextPoint(cocos2d::Point); // 
	cocos2d::Point getNextPoint(); // 供后面的节点获取位置
protected:
	cocos2d::Point nextPoint;
};

#endif