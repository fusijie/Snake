#include "GameLayer.h"


GameLayer::GameLayer(void)
{
}


GameLayer::~GameLayer(void)
{
	this->removeAllChildren();
}
bool GameLayer::init(){
	if(!Layer::init())
		return false;
	ball=NULL;
	auto listener = EventListenerTouchOneByOne::create(); 
	listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {return true;};
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this); 
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	Size size=Director::getInstance()->getVisibleSize();
	Point origin=Director::getInstance()->getVisibleOrigin();
	setGameStatus(GAME_STATUS_READY);

	shiftLand = schedule_selector(GameLayer::snakePlay);
        this->schedule(shiftLand, 0.3f);
        this->scheduleUpdate();

		snake=Snake::create();
		
		this->addChild(snake,2);
		
	return true;
}
void GameLayer::snakePlay(float at){
	
	if(getGameStatus()==GAME_STATUS_START){
		int width=SCREEN_WIDTH/SNAKE_WIDTH;
		int height=SCREEN_HEIGHT/SNAKE_WIDTH;
		Rect rect(1,1,width-2,height-2);
		if(snake->IsDie(rect)){
			setGameStatus(GAME_STATUS_OVER);
			delegator->onGameEnd();
			return;
		}
		if(IsEatBall()){
			snake->addSnakeNode();
			this->setBall();
		}
		else snake->play();
		bSetDirection=false;
		return;
	}
	
}
void GameLayer::onTouchEnded(Touch *touch, Event *unused_event){
	if(getGameStatus()==GAME_STATUS_READY){
		setGameStatus(GAME_STATUS_START);
		delegator->onGamePlay();
		snake->resetSnake();	
		setBall();
		ball->setVisible(true);
		bSetDirection=false;
		return ;
	}
	if(getGameStatus()==GAME_STATUS_OVER){
		setGameStatus(GAME_STATUS_READY);
		delegator->onGameStart();
		snake->removeAllChildren();
		ball->setVisible(false);
	}

	if(getGameStatus()==GAME_STATUS_START)
		this->setSnakeDirection(touch->getLocation());
}
void  GameLayer::setGameStatus(GameStatus status){
		gameStatus=status;
}
GameStatus GameLayer::getGameStatus(){
	return gameStatus;
}
void GameLayer::setSnakeDirection(Point p){
	if(bSetDirection) return;
	if(snake->getDirection()%2==0){
		if(p.x>SCREEN_WIDTH/2)
			snake->setDirection(SNAKE_HEAD_RIGHT);
		else
			snake->setDirection(SNAKE_HEAD_LEFT);
	}
	else{
		if(p.y>SCREEN_HEIGHT/2)
			snake->setDirection(SNAKE_HEAD_UP);
		else
			snake->setDirection(SNAKE_HEAD_DOWN);
	}
	bSetDirection=true;
}
bool GameLayer::IsSnakeContainsBall(Point p){
	for(SnakeNode *snakeNode:snake->getSnakeNodes())
				if(snakeNode->getBoundingBox().containsPoint(p))
					return true;
					
	return false;			

}
void GameLayer::setBall(){
	if(ball==NULL){
		ball=Sprite::create();
		this->addChild(ball,1);
	}
	vector<Point> tmpList;
	for(int i=1;i<SCREEN_WIDTH/SNAKE_WIDTH-1;i++)
		for(int j=1;j<SCREEN_HEIGHT/SNAKE_WIDTH-1;j++){
			Point point(i*SNAKE_WIDTH,j*SNAKE_WIDTH);
			if(!this->IsSnakeContainsBall(point))
				tmpList.push_back(point);
		}
		int tmpListSize=tmpList.size();			
		 if(tmpListSize>0){
				
			int tmp=CCRANDOM_0_1()*(tmpListSize-1);
			ball->setPosition(tmpList[tmp].x,tmpList[tmp].y);

			String str;
			tmp=CCRANDOM_0_1()*3;
			switch (tmp){
			case 0:
				str="football.png";
				break;
			case 1:
				str="Volleyball.png";
				break;
			case 2:
				str="basketball.png";
				break;
			}
			ball->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(str._string));
		 }

}
bool GameLayer::IsEatBall(){
	if(snake->getSnakeNodes().front()->boundingBox().containsPoint(ball->getPosition())){
		score++;
		return true;}
	return false;
}
