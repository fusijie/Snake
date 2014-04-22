#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

//枚举类型DIR_DEF，分别标识贪食蛇的移动方向
typedef enum {
	UP=1,
	DOWN,
	LEFT,
	RIGHT
}DIR_DEF;

//蛇每个节点都有自己的移动方向，因此，在节点类SnakeNode的定义中包含了行、列和方向3个成员
class SnakeNode :public cocos2d::Ref
{
public:
	int row;//行
	int col;//列
	int dir;//方向
};

//游戏欢迎画面，这个大家很熟的
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();//获取欢迎画面的Scene
    virtual bool init();  
	virtual void onEnter();
	virtual void onExit();
    
    CREATE_FUNC(HelloWorld);
};

//游戏帮助画面
class GameHelp :public cocos2d::Layer
{
public :
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	static cocos2d::Scene * createScene();//获取帮助画面
	CREATE_FUNC(GameHelp);
};

//游戏画面
class GameLayer :public cocos2d::Layer
{
public :
	static cocos2d::Scene * createScene();//获取游戏画面
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	virtual void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;//实现当前Layer的定义

	void onAcceleration(Acceleration* acc, Event* event);//重力事件的回调
	
	void logic01(float t);//update的回调
	
	CREATE_FUNC(GameLayer);

protected:
	SnakeNode *sHead;  //贪食蛇px py
	SnakeNode *sFood;  //食物
	cocos2d::Vector<Ref*> allBody;//蛇的身体
//	cocos2d::Texture2D * chead;
};


#endif // __HELLOWORLD_SCENE_H__
