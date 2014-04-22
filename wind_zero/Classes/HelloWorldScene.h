#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

typedef enum {
	UP=1,
	DOWN,
	LEFT,
	RIGHT
}DIR_DEF;

typedef enum {
	START=10,
	HELP,
	EXIT
}TAG_MENU;

class SnakeNode :public cocos2d::Ref
{
public:
	int row;
	int col;
	int dir;
	SnakeNode* preNode;
	cocos2d::Sprite* nodeSprite;
};

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    void menuCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(HelloWorld);
};

class GameHelp : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();  
	void menuBackToMain(cocos2d::Ref* pSender);
	CREATE_FUNC(GameHelp);
};

class GameScene : public cocos2d::Layer
{
public:
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void logic(float t);
	static cocos2d::Scene* createScene();
	virtual bool init();  
	void menuBackToMain(cocos2d::Ref* pSender);
	CREATE_FUNC(GameScene);
	
protected:
	SnakeNode* sHead;
	SnakeNode* sFood;
	cocos2d::Vector<SnakeNode*> allbody;
};

#endif // __HELLOWORLD_SCENE_H__
