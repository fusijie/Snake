#pragma once
#include "cocos2d.h"
USING_NS_CC;
class BackgroundLayer :
	public Layer
{
public:
	BackgroundLayer(void);
	virtual ~BackgroundLayer(void);
	virtual bool init();
	CREATE_FUNC(BackgroundLayer);
};

