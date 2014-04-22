//
//  SnakeHead.cpp
//  Snake
//
//  Created by cookie on 14-4-13.
//
//

#include "SnakeHead.h"

bool SnakeHead::init(){
    return true;
}

SnakeHead::SnakeHead(){
    this->direction = up;
}

SnakeHead::~SnakeHead(){
    
}

Direction SnakeHead::getDirec(){
    return this->direction;
}

void SnakeHead::setDirec(Direction di){
    this->direction = di;
}

