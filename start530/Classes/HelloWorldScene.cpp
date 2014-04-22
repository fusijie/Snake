#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);

    return scene;
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	CCLOG("HelloWorld onEnter");
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	
	///添加项菜单进入游戏游戏、帮助、退出游戏的按钮
	auto labelstart = LabelTTF::create("startGame","宋体",24);
	auto labelhelp = LabelTTF::create("GameHelp","宋体",24);
	auto labelexit = LabelTTF::create("exitGame","宋体",24);

	//进入游戏按钮
	auto mi01 = MenuItemLabel::create(labelstart,[](Ref* sender)
	{
		CCLOG("go to game");
		Director::getInstance()->replaceScene(GameLayer::createScene());//跳转到游戏场景
	});
	mi01->setPosition(Point(100,200)); 

	//帮助按钮
	auto mi02 = MenuItemLabel::create(labelhelp,[](Ref* sender)
	{
		CCLOG("go to help");
		Director::getInstance()->replaceScene(GameHelp::createScene());//跳转到帮助场景
	});
	mi02->setPosition(Point(100,150));

	//结束游戏
	auto mi03 = MenuItemLabel::create(labelexit,[](Ref* sender)
	{
		CCLOG("exit the game");
		Director::getInstance()->end();//退出游戏
	});
	mi03->setPosition(Point(100,50));
	auto pMenu = Menu::create(mi01,mi02,mi03, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu, 1);

    return true;
}

void HelloWorld::onExit()
{
	CCLOG("HelloWorld onExit");
}



bool GameHelp::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	auto labhelp = LabelTTF::create("please click screen to game","宋体",15);
	labhelp->setPosition(Point(0,280));
	this->addChild(labhelp);

	auto labback = LabelTTF::create("MainMenu","宋体",15);
	auto miback = MenuItemLabel::create(labback,[](Ref* sender)
	{
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	miback->setPosition(Point(0,0));

	auto pm = Menu::create(miback,NULL);
	this->addChild(pm);

	return true;
}

//获取帮助画面
Scene * GameHelp::createScene()
{
	auto scene = Scene::create();
	auto hl = GameHelp::create();
	scene->addChild(hl);
	return scene;
}

void GameHelp::onEnter()
{
	Layer::onEnter();
	CCLOG("GameHelp onEnter");
}
void GameHelp::onExit()
{
	CCLOG("GameHelp onExit");
}


//初始化游戏层
bool GameLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	auto labhelp = LabelTTF::create("this is game","宋体",15);
	labhelp->setPosition(Point(0,340));
	this->addChild(labhelp);

	auto labback = LabelTTF::create("MainMenu","宋体",15);
	auto miback = MenuItemLabel::create(labback,[](Ref* sender)
	{
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	miback->setPosition(Point(360,200));

	//chead=::CCTextureCache::sharedTextureCache()->addImage("head.png");

	//初始化蛇头坐标和食物的坐标
	sHead = new SnakeNode();
	sHead->row = rand()%10;
	sHead->col = rand()%10;

	//初始化食物的坐标
	sFood = new SnakeNode();
	sFood->row = rand()%10;
	sFood->col = rand()%10;

	//执行定时任务
	this->schedule(schedule_selector(GameLayer::logic01),0.5);
	return true;
}

//获取游戏场景
Scene * GameLayer::createScene()
{
	auto scene = Scene::create();
	auto hl = GameLayer::create();
	scene->addChild(hl);
	return scene;
}

void GameLayer::onEnter()
{
	Layer::onEnter();
	CCLOG("GameLayer onEnter");

	Device::setAccelerometerEnabled(true);//打开设备的重力感应
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAcceleration, this));//创建一个重力监听事件
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//将listener放到事件委托中
}
void GameLayer::onExit()
{
	CCLOG("GameLayer onExit");
}
void GameLayer::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
	///绘制形状
	::glLineWidth(2);//设定画线的宽度
	for(int i=0;i<11;i++)
	{
		DrawPrimitives::drawLine(Point(0,i*32),Point(320,i*32));//绘制条横线
		DrawPrimitives::drawLine(Point(i*32,0),Point(i*32,320));//绘制条竖线
	}

	//                    RGBA
	//DrawPrimitives::drawColor4B(ccc4(255,0,0,255));//设定画线的颜色

	//绘制蛇头
	DrawPrimitives::drawSolidRect(Point(sHead->col*32+2,sHead->row*32+2),
		Point(sHead->col*32+32,sHead->row*32+32),
		Color4F(Color3B(255,0,0)));

	//绘制食物
	DrawPrimitives::drawSolidRect(Point(sFood->col*32+2,sFood->row*32+2),
		Point(sFood->col*32+32,sFood->row*32+32),
		Color4F(Color3B(0,0,255)));

	//绘制身体
	for(int i=0;i<allBody.size();i++)
	{
		SnakeNode * node=(SnakeNode *)allBody.at(i);
		DrawPrimitives::drawSolidRect(Point(node->col*32+2,node->row*32+2),
		Point(node->col*32+32,node->row*32+32),
		Color4F(Color3B(0,0,255)));
	}

	/*Rect r(340,0,57,57);
	chead->drawInRect(r);
	Layer::draw();*/
}

void GameLayer::onAcceleration(Acceleration* acc, Event* event)
{
	void GameLayer::onAcceleration(Acceleration* acc, Event* event)
	{
		//0.5这东西很微妙的说
		if(acc->x<=-0.5)
		{
			sHead->dir=DIR_DEF::LEFT;
			log("LEFT");
		}
		else if(acc->x>=0.5)
		{
			sHead->dir=DIR_DEF::RIGHT;
			log("RIGHT");
		}
		else if(acc->y<=-0.5)
		{
			sHead->dir=DIR_DEF::DOWN;
			log("DOWN");
		}
		else if(acc->y>=0.5)
		{
			sHead->dir = DIR_DEF::UP;
			log("UP");
		}
		else
		{
			;
		}
	}
}

//定时器回调
void GameLayer::logic01(float t)
{   
	//移动蛇的身体
	for(int i = allBody.size()-1; i>=0; i--)
	{ 
		SnakeNode * sn = (SnakeNode *)allBody.at(i);//获取蛇身体上的某个节点
		
		if(i>0) 
		{ 
			//如果该节点不是第一个节点,那么该节点的下一个坐标就是其前一个点的坐标（这里不用多解释，玩过蛇的都懂）
			SnakeNode * snpre = (SnakeNode *)allBody.at(i-1);//获取前一个节点,把前一个节点的方向，坐标传给当前节点
			sn->dir = snpre->dir;
			sn->row = snpre->row;
			sn->col = snpre->col;
		}
		else if(i==0)
		{
			//如果i=0则是第一个节点，蛇头的坐标便是该节点的坐标
			sn->dir = sHead->dir;
			sn->row = sHead->row;
			sn->col = sHead->col;
		}
	}

	//移动蛇头,根据dir来判断蛇头的移动方向
	switch(sHead->dir)
	{
	case DIR_DEF::UP:
		sHead->row++;//上移
		if(sHead->row >= 10)
		{
			sHead->row=0;//超过顶部边界后便从底部出来
		}
		break;
	case DIR_DEF::DOWN:
		sHead->row--;
		if(sHead->row < 0)
		{
			sHead->row=9;
		}
		break;
	case DIR_DEF::LEFT:
		sHead->col--;
		if(sHead->col < 0)
		{
			sHead->col=9;
		}
		break;
	case DIR_DEF::RIGHT:
		sHead->col++;
		if(sHead->col >= 10)
		{
			sHead->col=0;
		}
		break;
	};  

	//碰撞检测
	//如果蛇头的横、列位置一样，说明蛇吃到了这个食物
	if(sHead->row == sFood->row && sHead->col == sFood->col)
	{ 
		//食物从当前位置消失，随机出现在下一个坐标
		sFood->row = rand()%10;
		sFood->col = rand()%10;

		//添加身体到集合
		SnakeNode * sn = new SnakeNode();//创建一个新的节点（也就是吃掉的那个食物），将其放到蛇的尾巴上
		SnakeNode * lastNode = NULL;
		//获取蛇的最后一个节点，如果allBody的size()为0，则说明蛇是第一次捕食，那么它的最后一个节点也就是蛇头啦。
		if(allBody.size()>0)
			lastNode = (SnakeNode *)allBody.back();
		else
			lastNode = sHead;//最后一个节点是蛇头

		//通过最后一个节点的方向来个新的节点初始化横、列坐标
		switch(lastNode->dir)
		{
		case DIR_DEF::UP:
			sn->row = lastNode->row-1;
			sn->col = lastNode->col;
			break;
		case DIR_DEF::DOWN:
			sn->row = lastNode->row+1;
			sn->col = lastNode->col;
			break;
		case DIR_DEF::LEFT:
			sn->row = lastNode->row;
			sn->col = lastNode->col+1;
			break;
		case DIR_DEF::RIGHT:
			sn->row=lastNode->row;
			sn->col=lastNode->col-1;
			break;
		}
		this->allBody.pushBack(sn);//将新的节点加入到蛇的身体中。
	}
}

