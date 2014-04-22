#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <iostream>

class HelloWorld : public cocos2d::Layer
{
    cocos2d::Vector<cocos2d::Sprite*> snake;
    int direction;
    float speed;
    cocos2d::Sprite* apple;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    
    void up_date(float dt);
    
    void move(int direction,int snake_ind);
    
    void testGameisOver(bool b);
    
    void testEat();
    
    void reSch();
    
    virtual void draw(cocos2d::Renderer* renderer, const kmMat4 &transform, bool transformUpdated) override;
    
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
