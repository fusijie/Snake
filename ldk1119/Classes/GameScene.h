#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GameScene :
	public Scene
{
public:
	GameScene(void);
	virtual ~GameScene(void);
	virtual bool init();
	CREATE_FUNC(GameScene);
};

