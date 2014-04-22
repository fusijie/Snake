//
//  SnakeHead.h
//  Snake
//
//  Created by cookie on 14-4-13.
//
//

#ifndef __Snake__SnakeHead__
#define __Snake__SnakeHead__

#include <iostream>

#include "cocos2d.h"
#include "Snake.h"

USING_NS_CC;

enum Direction {
    up = 0,
  down = 1,
  left = 2,
 right = 3,
};

class SnakeHead : public Snake{
private:
    Direction direction;
public:
    CREATE_FUNC(SnakeHead);
    virtual bool init();
    SnakeHead();
    ~SnakeHead();
    void setDirec(Direction di);
    Direction getDirec();
    
};

#endif /* defined(__Snake__SnakeHead__) */
