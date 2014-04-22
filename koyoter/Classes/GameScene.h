#ifndef _GAMESCENE_SCENE_H__
#define _GAMESCENE_SCENE_H__

#include "cocos2d.h"

enum DIRECTION
{
	RIGHT = 0 , 
	LEFT ,
	DOWN , 
	UP , 
	RESTART , 
	MENU
};

#define UP_TIME .25f

class GameScene : public cocos2d::Layer
{

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

protected:
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
private:
	cocos2d::Layer* layerGameMap;
	cocos2d::Sprite* spriteFood;
	cocos2d::Sprite* spriteHeader;
	cocos2d::Sprite* spriteFooter;
	cocos2d::MenuItem* menuItemRestart;
	cocos2d::MenuItem* menuItemMenu;
	cocos2d::Label* labelScore;
	cocos2d::Label* labelTime;
	int gameScore; // 当前分数
	long gameTime; // 此局开始了多久

	// 因为更新时间是固定的  怕当前更新蛇坐标还没完成又开始更新可能导致问题 所以加个标识符
	// (看代码更容易理解)
	bool isMoveEnd;

	// 各种按钮CB函数
	void menuCloseCallback(cocos2d::Ref* pSender);

	// 默认头部和脚步  所以初始化会为2
	int bones;

	// 蛇前进的方向
	DIRECTION currDirection;
	void changeDirection(DIRECTION);

	// 开始结束
	void start();
	void end();

	// 一定时间的回调，用于移动蛇节点和检查游戏状态
	void gameTask(float);
	void timeTask(float);

	// 移动
	void move();

	//检查是否自己咬自己 或者捡到食物
	void check();

	// 就是改变食物坐标 没必要重复创建就复用了
	void createFood();

	// 添加蛇身体节点
	void addBody();
};

#endif