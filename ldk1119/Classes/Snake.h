#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
const int SNAKE_HEAD_UP=0;
const int SNAKE_HEAD_DOWN=2;
const int SNAKE_HEAD_LEFT=3;
const int SNAKE_HEAD_RIGHT=1;
const int SNAKE_BODY_UP=4;
const int SNAKE_BODY_DOWN=6;
const int SNAKE_BODY_LEFT=7;
const int SNAKE_BODY_RIGHT=5;
const int SNAKE_CORNER_LEFT_UP=16;
const int SNAKE_CORNER_LEFT_DOWN=18;
const int SNAKE_CORNER_UP_LEFT=19;
const int SNAKE_CORNER_UP_RIGHT=17;
const int SNAKE_TAIL_UP=8;
const int SNAKE_TAIL_DOWN=10;
const int SNAKE_TAIL_LEFT=11;
const int SNAKE_TAIL_RIGHT=9;
const int SNAKE_CORNER_RIGHT_UP=12;
const int SNAKE_CORNER_RIGHT_DOWN=14;
const int SNAKE_CORNER_DOWN_LEFT=15;
const int SNAKE_CORNER_DOWN_RIGHT=13;
const float SNAKE_WIDTH=50;
class SnakeNode :
	public Sprite
{
public:
	SnakeNode(void);
	~SnakeNode(void);
	CREATE_FUNC(SnakeNode);
	//void setSnakeNodeRotiteByTag();
	void setSnakeNode(int x,int y,int tag);
	void setSnakeNode(int tag);
	SpriteFrame* getFrameNameByTag(int tag);
	void setPosition(int x,int y);
	void setPosition(Point p);
	Point getPosition();
	void setSnakeNodeRotate();

};
class Snake :
	public Node
{
public:
	Snake(void);
	~Snake(void);
	CREATE_FUNC(Snake);
	void createSnake();
	void play();
	void setDirection(int direction);
	int  getDirection();
	bool IsDie(Rect rect);
	Vector<SnakeNode*> getSnakeNodes();
		void addSnakeNode();
		void resetSnake();
private:
	void setSnakeNode(Sprite *SnakeNode);
	Point getNext();	
	int getInsertTag(int oldTag, int newTag);
	int direction;
	Vector<SnakeNode*> node; 
};

