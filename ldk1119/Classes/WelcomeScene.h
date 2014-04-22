#pragma once
#include "cocos2d.h"
#include "WelcomeLayer.h"
using namespace cocos2d;
using namespace std;

class WelcomeScene :
	public Scene
{
public:
	WelcomeScene(void);
	virtual ~WelcomeScene(void);
	bool virtual init();
	CREATE_FUNC(WelcomeScene);
};

