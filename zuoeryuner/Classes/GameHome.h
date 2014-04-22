#pragma once

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class GameHome : public Scene
{
public:
    CREATE_FUNC(GameHome);

protected:

private:
	virtual void onEnter();

	void close(Ref* sender);

	void play(Ref* sender);

	MenuItemLabel* createMenuTTF(const string& name,const Point& pos,const ccMenuCallback& callback);

	void createMenu();

	void createTitle();
};
