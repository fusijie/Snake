#pragma once
#include "cocos2d.h"
#include "time.h"
#include "Snake.h"

USING_NS_CC;
using namespace std;

typedef enum _game_status {
	GAME_STATUS_READY ,
	GAME_STATUS_START,
	GAME_STATUS_OVER,
	GAME_STATUS_PLAY
} GameStatus;
const int CAUTI_LEFT=100;
const int GAME_WIDTH=8;
const int GAME_HEIGHT=16;
const int SCREEN_WIDTH=480;
const int SCREEN_HEIGHT=800;
//const int CAU_
class StatusDelegate {
public:
	
	virtual void onGamePlay(void) = 0;

	virtual void onGameStart(void) = 0;

	virtual void onGameEnd(void) = 0;
};
class GameLayer :
	public Layer
{
public:
	GameLayer(void);
	virtual ~GameLayer(void);
	virtual bool  init();
	CREATE_FUNC(GameLayer);
	GameStatus getGameStatus();
	void setGameStatus(GameStatus status);

private:
	//void update(float delta);
	
	StatusDelegate *delegate;
	CC_SYNTHESIZE(StatusDelegate*,delegator,Delegator);
	void onTouchEnded(Touch *touch, Event *unused_event) ;
	void setSnakeDirection(Point p);
	void setBall();
	bool IsEatBall();
	bool IsSnakeContainsBall(Point p);
	SEL_SCHEDULE  shiftLand;
	void snakePlay(float dt);
	GameStatus gameStatus;
	Snake *snake;
	bool bSetDirection;
	Sprite *ball;
	int score;
};

