//
//  SnakeNode.h
//  Snake
//
//  Created by 童翾 on 14-4-10.
//
//

#ifndef __Snake__SnakeNode__
#define __Snake__SnakeNode__

#include <iostream>
#include "cocos2d.h"

enum DIR_DEF
{
    UP = 1,
    DOWN,
    LEFT,
    RIGHT
};
class SnakeNode: public cocos2d::Ref
{

public:
    DIR_DEF dir;
    int row, col;
};

#endif /* defined(__Snake__SnakeNode__) */
