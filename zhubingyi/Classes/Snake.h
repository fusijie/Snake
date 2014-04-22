//
//  Snake.h
//  Snake
//
//  Created by cookie on 14-4-13.
//
//

#ifndef __Snake__Snake__
#define __Snake__Snake__

#include <iostream>

#include "cocos2d.h"

using namespace cocos2d;

class Snake : public Node{
    
private:
    Sprite* snakenode;
public:
    void setNode(Sprite* node);
    Sprite* getNode();
    CREATE_FUNC(Snake);
    virtual bool init();

};


#endif /* defined(__Snake__Snake__) */
