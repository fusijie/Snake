#pragma once

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class Game : public Scene
{
public:
	CREATE_FUNC(Game);
protected:

private:
	enum SnakeDirection
	{
		UP_OR_DOWN = 1,
		UP = 1,
		DOWN = -1,

		LEFT_OR_RIGHT = 2,
		LEFT = 2,
		RIGHT = -2
	};

	virtual void onEnter();
	
	DrawNode* createDrawNode(const Point& pos);

	void initSnake();

	void createSnakeNode();

	void createApple();

	void snakeMove(float);

	void snakeHeadMove();

	void touchSnakeDirection(const Point& tochPoint);

	bool snakeIsAapple();

	bool snakeIsDie();

	void snakeDie();



	static Size kSnakeNodeSize;

	vector<DrawNode*> _snake;

	DrawNode* _apple;

	SnakeDirection _snakeDirection;

	SnakeDirection _touchSnakeDirection;
	bool _istouchSnakeDirection;
};