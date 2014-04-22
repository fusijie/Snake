#pragma once
#include "cocos2d.h"

#include "SimpleAudioEngine.h"
#include "CCMenuItem.h"
using namespace std;
using namespace cocos2d;
class WelcomeLayer :
	public Layer
{
public:
	WelcomeLayer(void);
	virtual ~WelcomeLayer(void);
		virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(WelcomeLayer);
private:
	void menuStartCallback(Ref *sender);
};

