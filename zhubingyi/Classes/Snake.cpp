//
//  Snake.cpp
//  Snake
//
//  Created by cookie on 14-4-13.
//
//

#include "Snake.h"


Sprite* Snake::getNode(){
    return this->snakenode;
}

void Snake::setNode(Sprite* node){
    this->snakenode = node;
    this->addChild(snakenode);
}

bool Snake::init(){
    return true;
}

