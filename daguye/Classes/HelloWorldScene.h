#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
//标识贪食蛇的移动方向
typedef enum {
	UP=1,
	DOWN,
	LEFT,
	RIGHT
}DIR_DEF;

//定义每一节蛇元素的属性，包含了所在行，列，移动方向
class SnakeNode :public cocos2d::Ref{
public:
	int row;//行
	int col;//列
	int dir;//方向
};

//游戏主菜单画面
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();//创建主菜单画面的场景
	virtual bool init();  //初始化操作
	//菜单项点击事件
    void menuCloseCallback(Ref* pSender);
	void menuStartCallback(Ref* pSender);
	void menuHelpCallback(Ref* pSender);
    
    CREATE_FUNC(HelloWorld);
};

//游戏帮助画面
class GameHelp :public cocos2d::Layer
{
public :
	virtual bool init();//初始化
	//按钮事件监听
	void menuGoGameCallback(Ref* pSender);
	void menuGoMainCallback(Ref* pSender);
	static cocos2d::Scene * createScene();//创建帮助画面
	CREATE_FUNC(GameHelp);
};

//游戏画面
class GameLayer :public cocos2d::Layer
{
protected:
	SnakeNode *sHead;  //创建蛇对象
	SnakeNode *sFood;  //食物对象
	cocos2d::Vector<Ref*> allBody;//蛇的身体
	cocos2d::Texture2D * chead;
public :
	virtual bool init();//初始化

	virtual void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;

	//监听触摸事件
	bool onTouchBegan(cocos2d::Touch* touch, Event  *event);
	
	void timesthing(float t);//定时事件
	static cocos2d::Scene * createScene();//创建游戏画面
	CREATE_FUNC(GameLayer);
};



#endif // __HELLOWORLD_SCENE_H__
