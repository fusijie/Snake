#ifndef __MENUSCENE_SCENE_H__
#define __MENUSCENE_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MenuScene);

private:
	void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif