//
//  GameLayer.h
//  Snake
//
//  Created by fireblackill on 14-4-10.
//
//

#ifndef __Snake__GameLayer__
#define __Snake__GameLayer__

#include <iostream>
#include "SnakeNode.h"

class GameLayer: public cocos2d::Layer
{
private:
    
    SnakeNode* m_head;
    SnakeNode* m_food;
    cocos2d::Vector<SnakeNode*> m_body;
    
public:
    virtual bool init();
    virtual void draw(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated);
    void update(float dt);
    static cocos2d::Scene* createScene();
    CREATE_FUNC(GameLayer);
    void menuBackToMain(cocos2d::Ref *pSender);
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    
};

#endif /* defined(__Snake__GameLayer__) */
