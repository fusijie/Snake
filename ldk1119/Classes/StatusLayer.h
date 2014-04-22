#pragma once
#include "cocos2d.h"
#include "GameLayer.h"
USING_NS_CC;

class StatusLayer :
	public Layer, public StatusDelegate
{
public:
	StatusLayer(void);
	virtual ~StatusLayer(void);
	virtual bool init();
	CREATE_FUNC(StatusLayer);
	virtual void onGameStart(void) ;
	virtual void onGamePlay(void) ;
	virtual void onGameEnd(void);
private:

	Sprite* statusSprite;
	Label* label;

};

