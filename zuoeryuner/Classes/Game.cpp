#include "Game.h"

Size Game::kSnakeNodeSize = Size(30,30);

void Game::onEnter()
{
	Scene::onEnter();

	this->schedule(schedule_selector(Game::snakeMove),0.2f);

	_istouchSnakeDirection = false;
	_snakeDirection = RIGHT;
	initSnake();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch,Event*){ return true; };
	listener->onTouchEnded = [=](Touch* touch,Event*){ touchSnakeDirection(touch->getLocation()); };
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	createApple();
}

void Game::createSnakeNode()
{
	auto drawNode = createDrawNode(Point::ZERO);
	_snake.push_back(drawNode);
}

DrawNode* Game::createDrawNode( const Point& pos )
{
	auto drawNode = DrawNode::create();
	Size size(kSnakeNodeSize);
	Point point = Point(-size.width/2,size.height/2);
	Point points[4] = {
		point,
		Point(point.x,point.y-size.height),
		Point(point.x + size.width,point.y-size.height),
		Point(point.x+size.width,point.y)};
	drawNode->drawPolygon(points,4,Color4F::WHITE,1,Color4F::RED);
	drawNode->setPosition(pos);
	this->addChild(drawNode);
	return drawNode;
}

void Game::createApple()
{
	Point pos;
	bool b = false;
	do 
	{
		Size size = Director::getInstance()->getVisibleSize();
		pos.x = ( (int)(CCRANDOM_0_1() * (size.width/kSnakeNodeSize.width-1)) + 0.5f ) * kSnakeNodeSize.width;
		pos.y = ( (int)(CCRANDOM_0_1() * (size.height/kSnakeNodeSize.height-1)) + 0.5f ) * kSnakeNodeSize.height;
		for (auto m : _snake)
		{
			if (m->getPosition().equals(pos))
			{
				b = true;
				break;
			}
			else
			{
				b = false;
			}
		}
	} while (b);
	_apple = createDrawNode(pos);
}

void Game::snakeMove( float )
{
	if (_istouchSnakeDirection)
	{
		_snakeDirection = _touchSnakeDirection;
	}

	for (size_t i = _snake.size()-1; i > 0 ;--i)
	{
		auto pos = _snake[i-1]->getPosition();
		_snake[i]->setPosition(pos);
	}
	snakeHeadMove();

	if (snakeIsDie())
	{
		snakeDie();
	}
	if (snakeIsAapple())
	{
		createSnakeNode();
	}
}

void Game::initSnake()
{
	_snake.clear();
	for (int i = 0; i < 3;++i)
	{
		auto drawNode = createDrawNode(Point(0-kSnakeNodeSize.width*i,0)+Point(kSnakeNodeSize*12.5f));
		_snake.push_back(drawNode);
	}
}

void Game::touchSnakeDirection( const Point& tochPoint )
{
	_istouchSnakeDirection = false;
	if (abs(_snakeDirection) == UP_OR_DOWN)
	{
		if (tochPoint.x < _snake[0]->getPosition().x) 
		{
			_touchSnakeDirection = LEFT;
		}
		else
		{
			_touchSnakeDirection = RIGHT;
		}
		_istouchSnakeDirection = true;
	}
	else if (abs(_snakeDirection) == LEFT_OR_RIGHT)
	{
		if (tochPoint.y < _snake[0]->getPosition().y) 
		{
			_touchSnakeDirection = DOWN;
		}
		else
		{
			_touchSnakeDirection = UP;
		}
		_istouchSnakeDirection = true;
	}
}

bool Game::snakeIsDie()
{
	auto pos = _snake[0]->getPosition();
	for (size_t i = 1; i < _snake.size(); ++i)
	{
		if (_snake[i]->getPosition().equals(pos))
		{
			return true;
		}
	}
	auto size = Director::getInstance()->getVisibleSize();
	Rect rect(kSnakeNodeSize.width/2,kSnakeNodeSize.height/2,
		size.width - kSnakeNodeSize.width,size.height - kSnakeNodeSize.height);
	if (!rect.containsPoint(pos))
	{
		return true;
	}
	return false;
}

void Game::snakeDie()
{
	this->unscheduleAllSelectors();

	auto title = Label::create("Game Over","fonts/Marker Felt.ttf",50);
	title->setAnchorPoint(Point::ANCHOR_MIDDLE);
	title->setPosition(480,520);
	title->enableShadow(Color3B::RED);
	this->addChild(title);

	auto closeLabel = Label::create("Restart","fonts/Marker Felt.ttf",40);
	closeLabel->enableShadow(Color3B::GREEN);
	auto menuItemLabel = MenuItemLabel::create(closeLabel,[](Ref*){
		Director::getInstance()->replaceScene(Game::create()); });
	auto menu = Menu::create(menuItemLabel,nullptr);
	this->addChild(menu);
}

void Game::snakeHeadMove()
{
	switch (_snakeDirection)
	{
	case Game::UP:
		_snake[0]->setPositionY(_snake[0]->getPositionY()+kSnakeNodeSize.height);
		break;
	case Game::DOWN:
		_snake[0]->setPositionY(_snake[0]->getPositionY()-kSnakeNodeSize.height);
		break;
	case Game::LEFT:
		_snake[0]->setPositionX(_snake[0]->getPositionX()-kSnakeNodeSize.width);
		break;
	case Game::RIGHT:
		_snake[0]->setPositionX(_snake[0]->getPositionX()+kSnakeNodeSize.width);
		break;
	default:
		break;
	}
}

bool Game::snakeIsAapple()
{
	auto posApple = _apple->getPosition();
	auto posSnake = _snake[0]->getPosition();
	if (posApple.equals(posSnake))
	{
		_apple->removeFromParent();
		createApple();
		return true;
	}
	return false;
}