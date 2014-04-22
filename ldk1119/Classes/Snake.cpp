#include "Snake.h"


SnakeNode::SnakeNode(void){}
SnakeNode::~SnakeNode(void){}
void SnakeNode::setSnakeNode(int px,int py,int tag ){
	//SnakeNode->	
	if(tag<=SNAKE_HEAD_LEFT) this->setAnchorPoint(Point(0.5,0.431));
	this->setSnakeNode(tag);
	this->setPosition(px,py);
	
}
void SnakeNode::setSnakeNode(int tag){
	this->setTag(tag);
	this->setSpriteFrame(this->getFrameNameByTag( tag));
	this->setSnakeNodeRotate();
}
void SnakeNode::setSnakeNodeRotate(){
	int tag=this->getTag();
		int rotate=90*(tag%4);
		if(tag==SNAKE_CORNER_RIGHT_UP||tag==SNAKE_CORNER_DOWN_LEFT)
		rotate=180;
		if(tag==SNAKE_CORNER_RIGHT_DOWN || tag==SNAKE_CORNER_UP_LEFT)
			rotate=90;
		if(tag==SNAKE_CORNER_LEFT_UP||tag==SNAKE_CORNER_DOWN_RIGHT)
			rotate=270;
		if(tag==SNAKE_CORNER_LEFT_DOWN||tag==SNAKE_CORNER_UP_RIGHT)
			rotate=0;
	
	this->setRotation(rotate);
}
void SnakeNode::setPosition(int x,int y){
	Sprite::setPosition(x*SNAKE_WIDTH,y*SNAKE_WIDTH);
}
void SnakeNode::setPosition(Point p){
	Sprite::setPosition(p.x*SNAKE_WIDTH,p.y*SNAKE_WIDTH);
}
Point SnakeNode::getPosition(){
	Point p=Sprite::getPosition();
	p.x=(int)p.x/SNAKE_WIDTH;
	p.y=(int)p.y/SNAKE_WIDTH;	
	return p;
}
SpriteFrame* SnakeNode::getFrameNameByTag(int tag){
	switch(tag){
	case SNAKE_HEAD_UP:
	case SNAKE_HEAD_DOWN:
	case SNAKE_HEAD_LEFT:
	case SNAKE_HEAD_RIGHT:
		return SpriteFrameCache::getInstance()->getSpriteFrameByName("snake_head.png");
	case SNAKE_BODY_UP:
	case SNAKE_BODY_DOWN:
	case SNAKE_BODY_LEFT:
	case SNAKE_BODY_RIGHT:
		return SpriteFrameCache::getInstance()->getSpriteFrameByName("snake_body.png");
	case SNAKE_CORNER_DOWN_LEFT:
	case SNAKE_CORNER_LEFT_DOWN:
	case SNAKE_CORNER_RIGHT_DOWN:
	case SNAKE_CORNER_UP_LEFT:
	case SNAKE_CORNER_DOWN_RIGHT:
	case SNAKE_CORNER_LEFT_UP:
	case SNAKE_CORNER_RIGHT_UP:
	case SNAKE_CORNER_UP_RIGHT:
		return SpriteFrameCache::getInstance()->getSpriteFrameByName("snake_corner.png");
	case SNAKE_TAIL_UP:
	case SNAKE_TAIL_DOWN:
	case SNAKE_TAIL_LEFT:
	case SNAKE_TAIL_RIGHT:
		return SpriteFrameCache::getInstance()->getSpriteFrameByName("snake_tail.png");
	}
	return NULL;
}
/////*********************************************************//
//
//
//
//
//**************************************************************//
Snake::Snake(void)
{
}


Snake::~Snake(void)
{
	
}
void Snake::createSnake(){
	Size size=Director::getInstance()->getVisibleSize();
	Point origin=Director::getInstance()->getVisibleOrigin();
	this->setAnchorPoint(Point::ZERO);
	SnakeNode *snakeNode=SnakeNode::create();
	snakeNode->setSnakeNode(7,3,SNAKE_HEAD_UP);
	node.pushBack(snakeNode);
	this->addChild(snakeNode);
	SnakeNode *snakeNode1=SnakeNode::create();
	snakeNode1->setSnakeNode(7,2,SNAKE_BODY_UP);
	node.pushBack(snakeNode1);
	this->addChild(snakeNode1);
	SnakeNode *snakeNode2=SnakeNode::create();
	snakeNode2->setSnakeNode(7,1,SNAKE_TAIL_UP);
	node.pushBack(snakeNode2);
	this->addChild(snakeNode2);
	setDirection(SNAKE_HEAD_UP);

}
void Snake::setDirection(int direction){
	this->direction=direction;
}
int Snake::getDirection(){
	return this->direction;
}
void Snake::addSnakeNode(){
	SnakeNode *snakeNode=SnakeNode::create();
	snakeNode->setPosition(node.front()->getPosition());
	snakeNode->setSnakeNode(this->getInsertTag(node.front()->getTag(),this->getDirection()));
	node.insert(1,snakeNode);
	this->addChild(snakeNode);
	if(node.front()->getTag()!=this->getDirection()){
		node.front()->setTag(this->getDirection());			
		node.front()->setSnakeNodeRotate();
	}
	node.front()->setPosition(getNext());
}

void Snake::play(){
	SnakeNode *snakeNode=node.back();
	//int tag=snakeNode->getTag();
	snakeNode->setPosition(node.front()->getPosition());
	snakeNode->setSnakeNode(this->getInsertTag(node.front()->getTag(),this->getDirection()));
	node.insert(1,snakeNode);
	if(node.front()->getTag()!=this->getDirection()){
		node.front()->setTag(this->getDirection());			
		node.front()->setSnakeNodeRotate();
	}
	node.front()->setPosition(getNext());
	
	node.popBack();
	snakeNode=node.back();
	snakeNode->setSnakeNode(snakeNode->getTag()%4+8);
}
Point Snake::getNext(){
	SnakeNode *snakeNode=node.front();
	Point point=snakeNode->getPosition();
	switch(snakeNode->getTag()){
	case SNAKE_HEAD_UP:
		++point.y;
		break;
	case SNAKE_HEAD_DOWN:
		--point.y;
		break;
	case SNAKE_HEAD_LEFT:
		--point.x;
		break;
	case SNAKE_HEAD_RIGHT:
		++point.x;
		break;
	}
	return point;
}
int Snake::getInsertTag(int oldTag,int newTag){
	if(oldTag==newTag)return oldTag+4;
	if(oldTag==SNAKE_HEAD_RIGHT&&newTag==SNAKE_HEAD_UP)
		return SNAKE_CORNER_RIGHT_UP;
	if(oldTag==SNAKE_HEAD_DOWN&&newTag==SNAKE_HEAD_LEFT)
		return SNAKE_CORNER_DOWN_LEFT;
	if(oldTag==SNAKE_HEAD_RIGHT&&newTag==SNAKE_HEAD_DOWN)
		return SNAKE_CORNER_RIGHT_DOWN;
	if(oldTag==SNAKE_HEAD_UP&&newTag==SNAKE_HEAD_LEFT)
		return SNAKE_CORNER_UP_LEFT;
	if(oldTag==SNAKE_HEAD_LEFT&&newTag==SNAKE_HEAD_UP)
		return SNAKE_CORNER_LEFT_UP;
	if(oldTag==SNAKE_HEAD_DOWN &&newTag==SNAKE_HEAD_RIGHT)
		return SNAKE_CORNER_DOWN_RIGHT;
	if(oldTag==SNAKE_HEAD_LEFT && newTag==SNAKE_HEAD_DOWN)
		return SNAKE_CORNER_LEFT_DOWN;
	if(oldTag==SNAKE_HEAD_UP&&newTag==SNAKE_HEAD_RIGHT)
		return SNAKE_CORNER_UP_RIGHT;
	return -1;
}
bool Snake::IsDie(Rect rect){
	
	if(!rect.containsPoint(node.front()->getPosition()))
		return true;
	Rect box=node.front()->getBoundingBox();
	auto point=node.front()->getPosition();
		point.x=point.x*SNAKE_WIDTH;
		point.y=point.y*SNAKE_WIDTH;
	for(SnakeNode *snakenode:node){
		if(snakenode->getTag()>SNAKE_HEAD_LEFT)
			if(snakenode->getBoundingBox().containsPoint(point))
				return true;
	}

	return false;
}
Vector<SnakeNode*> Snake::getSnakeNodes(){
	return node;
}
void Snake::resetSnake(){
	this->removeAllChildren();
	node.clear();
	this->createSnake();
}