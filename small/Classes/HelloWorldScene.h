#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

const unsigned int LEN = 32;

#pragma warning(once:4996)

#include "cocos2d.h"



enum eMenuTag
{
    eStart = 1,
    eHelp,
    eExit,
    eClose,
};

typedef enum {
    UP = 1,
    DOWN,
    LEFT,
    RIGHT
}DIR_DEF;

class SnakeNode : public cocos2d::CCObject{
public:
    int row;
    int col;
    int dir;
};

//游戏欢迎画面
class HelloWorld : public cocos2d::CCLayer
{
public:
    CREATE_FUNC(HelloWorld);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    static cocos2d::CCScene* scene();//获取欢迎画面的Scene
    void menuCloseCallback(cocos2d::CCObject* pSender);    
};

//游戏帮助画面
class GameHelp : public cocos2d::CCLayer{
public:
    CREATE_FUNC(GameHelp);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    static cocos2d::CCScene * scene();//获取帮助画面
    void menuBackToMain(cocos2d::CCObject *pSender);//返回主菜单    
};

//游戏画面
class GameLayer : public cocos2d::CCLayer{
public:
    CREATE_FUNC(GameLayer);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    static cocos2d::CCScene * scene();//获取游戏画面
    void menuBackToMain(cocos2d::CCObject *pSender);//返回主菜单
    //virtual void draw();//实现当前Layer的定义
    virtual void draw(cocos2d::Renderer *renderer, const kmMat4& transform, bool transformUpdated);
    //virtual void registerWithTouchDispatcher(void);
    virtual bool onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void onTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void onTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void logic01(float t);    
protected:
    SnakeNode *sHead;  //贪食蛇px py
    SnakeNode *sFood;  //食物
    cocos2d::CCArray * allBody;//蛇的身体
    cocos2d::CCTexture2D * chead;
    unsigned char m_line; //正方形的网格有多少条线
    unsigned int m_len; //网格的边长
};

#endif  // __HELLOWORLD_SCENE_H__
