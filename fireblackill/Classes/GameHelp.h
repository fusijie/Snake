//
//  GameHelp.h
//  Snake
//
//  Created by fireblackill on 14-4-10.
//
//

#ifndef __Snake__GameHelp__
#define __Snake__GameHelp__

#include <iostream>
#include "cocos2d.h"

class GameHelp : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameHelp);
    void menuBackToMain(cocos2d::Ref *pSender);
};

#endif /* defined(__Snake__GameHelp__) */
