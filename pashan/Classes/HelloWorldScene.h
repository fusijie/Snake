#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

typedef enum {
	START=10,HELP,EXIT
} TAG_MENU;

typedef enum {     
	UP=1,DOWN,LEFT,RIGHT 
} DIR_DEF;

static int highScore=0;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    void menuCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(HelloWorld);
};

class SnakeNode :public cocos2d::Ref 
{ 
public:     
	int x;
	int y;
	cocos2d::Sprite* sprite;
};

class DirNode :public cocos2d::Ref
{
public:
	int dir;
};


class GameScene : public cocos2d::Layer 
{ 
public:     
	static cocos2d::Scene* createScene();     
	virtual bool init();       
	void menuBackToMain(cocos2d::Ref* pSender);     
	CREATE_FUNC(GameScene);

    int winWidth;
    int winHeight;
    int score;
    bool gameOverFlag;
    float gameOverDelay;
    float speed;
    SnakeNode* egg;
    cocos2d::Vector<SnakeNode*> snake;
    int controlDir;
    int snakeLength;
    int snakeNodeWidth;
    int snakeStep;
    int snakeAllStep;
    cocos2d::Vector<DirNode*> dirChain;//方向链
    cocos2d::Label* labelScore;
    
    SnakeNode* genEgg();
    void snakeMove(int dir);
    
    void play(float t);
    void gameOver();
    bool onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* event );
    void onTouchEnded( cocos2d::Touch* touch, cocos2d::Event* event );
    int touch_x;
    int touch_y;
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    bool borderDetection(cocos2d::Sprite* sprite);
    bool collisionDetection(SnakeNode* node1,SnakeNode* node2);
};
#endif // __HELLOWORLD_SCENE_H__
