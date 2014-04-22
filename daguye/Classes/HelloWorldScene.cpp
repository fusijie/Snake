#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);

	return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//在界面上添加菜单内容

	//添加关闭程序按钮
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",//默认显示图片
		"CloseSelected.png",//点击按下显示图片
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));//绑定点击事件

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));//设定显示位置为屏幕宽度-控件自身宽高一半。也就是显示在右下角


	//添加开始按钮
	auto startMenu = MenuItemImage::create(
		"btn_start.png",
		"btn_start.png",
		CC_CALLBACK_1(HelloWorld::menuStartCallback, this));

	startMenu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 50));

	//添加帮助按钮
	auto helpMenu = MenuItemImage::create(
		"btn_help.png",
		"btn_help.png",
		CC_CALLBACK_1(HelloWorld::menuHelpCallback, this));

	helpMenu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//添加退出按钮
	auto exitMenu = MenuItemImage::create(
		"btn_exit.png",
		"btn_exit.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	exitMenu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 50));


	//创建菜单载体，将上面的菜单内容都添加到载体中
	auto pMenu = Menu::create(startMenu, helpMenu, exitMenu, closeItem, NULL);//添加制定的菜单项
	pMenu->setPosition(Point::ZERO);//设置显示位置
	this->addChild(pMenu, 1);//添加到场景中


	//制定游戏背景
	auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	//------------------------

	return true;
}


//退出按钮事件
void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Director::getInstance()->replaceScene(GameHelp::createScene());
	Director::getInstance()->end();
}
//开始游戏按钮事件
void HelloWorld::menuStartCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameLayer::createScene());
	//Director::getInstance()->end();
}
//帮助按钮事件
void HelloWorld::menuHelpCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameHelp::createScene());
	//Director::getInstance()->end();
}




bool GameHelp::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	//添加退出按钮
	auto gotogameMenu = MenuItemImage::create(
		"btn_gotogame.png",
		"btn_gotogame.png",
		CC_CALLBACK_1(GameHelp::menuGoGameCallback, this));

	gotogameMenu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto goMainMenu = MenuItemImage::create(
		"btn_gomain.png",
		"btn_gomain.png",
		CC_CALLBACK_1(GameHelp::menuGoMainCallback, this));

	goMainMenu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 50));

	auto pMenu = Menu::create(gotogameMenu, goMainMenu, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu, 1);

	auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);
	return true;
}
//帮助按钮事件
void GameHelp::menuGoGameCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameLayer::createScene());
}

//帮助按钮事件
void GameHelp::menuGoMainCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}



//获取帮助画面
Scene * GameHelp::createScene()
{
	auto scene = Scene::create();
	auto hl = GameHelp::create();
	scene->addChild(hl);
	return scene;
}

int isfirst = 0;
//初始化游戏层
bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();


	auto goMainMenu = MenuItemImage::create(
		"btn_gomain.png",
		"btn_gomain.png",
		[](Ref* sender){
			Director::getInstance()->replaceScene(HelloWorld::createScene());
		});

	goMainMenu->setPosition(Point(origin.x + visibleSize.width - goMainMenu->getContentSize().width / 2,
		origin.y +visibleSize.height + goMainMenu->getContentSize().height / 2));

	auto pMenu = Menu::create(goMainMenu, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu, 1);


	auto labhelp = LabelTTF::create("this is game", "Arial", 15);
	labhelp->setPosition(Point(visibleSize.width + origin.x, visibleSize.height + origin.y));
	this->addChild(labhelp);

	auto labback = LabelTTF::create("MainMenu", "Arial", 15);
	auto miback = MenuItemLabel::create(labback, [](Ref* sender)
	{
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	miback->setPosition(Point(visibleSize.width + origin.x - miback->getContentSize().width / 2, visibleSize.height + origin.y - miback->getContentSize().height / 2));

	this->addChild(miback);



	chead = ::CCTextureCache::sharedTextureCache()->addImage("head.png");
	//监听触摸事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);//指定触摸的回调函数    
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//将listener放入事件委托中  

	//初始化蛇头坐标和食物的坐标
	sHead = new SnakeNode();
	sHead->row = rand() % 10;
	sHead->col = rand() % 10;

	//初始化食物的坐标
	sFood = new SnakeNode();
	sFood->row = rand() % 10;
	sFood->col = rand() % 10;


	//执行定时事件
	this->schedule(schedule_selector(GameLayer::timesthing), 0.5);
	return true;
}

//创建游戏场景
Scene * GameLayer::createScene()
{
	auto scene = Scene::create();
	auto hl = GameLayer::create();
	scene->addChild(hl);
	return scene;

}



void GameLayer::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	///绘制形状
	::glLineWidth(2);//设定画线的宽度
	for (int i = 0; i < 11; i++)
	{
		DrawPrimitives::drawLine(Point(0, i * 32), Point(320, i * 32));//绘制条横线
		DrawPrimitives::drawLine(Point(i * 32, 0), Point(i * 32, 320));//绘制条竖线
	}


	//绘制蛇头
	DrawPrimitives::drawSolidRect(Point(sHead->col * 32 + 2, sHead->row * 32 + 2),
		Point(sHead->col * 32 + 32, sHead->row * 32 + 32),
		Color4F(Color3B(255, 0, 0)));

	//绘制食物
	DrawPrimitives::drawSolidRect(Point(sFood->col * 32 + 2, sFood->row * 32 + 2),
		Point(sFood->col * 32 + 32, sFood->row * 32 + 32),
		Color4F(Color3B(0, 0, 255)));

	//绘制身体
	for (int i = 0; i < allBody.size(); i++)
	{
		SnakeNode * node = (SnakeNode *)allBody.at(i);
		DrawPrimitives::drawSolidRect(Point(node->col * 32 + 2, node->row * 32 + 2),
			Point(node->col * 32 + 32, node->row * 32 + 32),
			Color4F(Color3B(0, 0, 255)));
	}

}

bool GameLayer::onTouchBegan(Touch* touch, Event  *event)
{
	auto p = touch->getLocation();

	int nowrow;	//当前用户触摸的行
	nowrow = ((int)p.y) / 32;
	int nowcol;	//当前用户触摸的列
	nowcol = ((int)p.x) / 32;

	if (abs(nowrow - sHead->row) > abs(nowcol - sHead->col)) //上下移动
	{
		if (nowrow > sHead->row)
		{
			sHead->dir = DIR_DEF::UP;
		}
		else
		{
			sHead->dir = DIR_DEF::DOWN;
		}

	}
	else    //左右移动
	{
		if (nowcol > sHead->col)
		{
			sHead->dir = DIR_DEF::RIGHT;
		}
		else
		{
			sHead->dir = DIR_DEF::LEFT;
		}
	}
	CCLOG("rand %d", rand());
	CCLOG("you touchbegan%f,%f", p.x, p.y);

	return true;
}



//定时器回调
void GameLayer::timesthing(float t)
{
	//移动蛇的身体
	for (int i = allBody.size() - 1; i >= 0; i--)
	{
		SnakeNode * sn = (SnakeNode *)allBody.at(i);

		if (i > 0)
		{
			SnakeNode * snpre = (SnakeNode *)allBody.at(i - 1);
			sn->dir = snpre->dir;
			sn->row = snpre->row;
			sn->col = snpre->col;
		}
		else if (i == 0)
		{
			//移动第一个节点
			sn->dir = sHead->dir;
			sn->row = sHead->row;
			sn->col = sHead->col;
		}
	}

	//移动蛇头
	switch (sHead->dir)
	{
	case DIR_DEF::UP:
		sHead->row++;
		if (sHead->row >= 10)
		{
			sHead->row = 0;
		}
		break;
	case DIR_DEF::DOWN:
		sHead->row--;
		if (sHead->row < 0)
		{
			sHead->row = 9;
		}
		break;
	case DIR_DEF::LEFT:
		sHead->col--;
		if (sHead->col < 0)
		{
			sHead->col = 9;
		}
		break;
	case DIR_DEF::RIGHT:
		sHead->col++;
		if (sHead->col >= 10)
		{
			sHead->col = 0;
		}
		break;
	};

	//碰撞检测
	if (sHead->row == sFood->row && sHead->col == sFood->col)
	{
		//食物消失
		sFood->row = rand() % 10;
		sFood->col = rand() % 10;

		//添加身体到集合
		SnakeNode * sn = new SnakeNode();
		SnakeNode * lastNode = NULL;
		if (allBody.size() > 0)
			lastNode = (SnakeNode *)allBody.back();
		else
			lastNode = sHead;

		switch (lastNode->dir)
		{
		case DIR_DEF::UP:
			sn->row = lastNode->row - 1;
			sn->col = lastNode->col;
			break;
		case DIR_DEF::DOWN:
			sn->row = lastNode->row + 1;
			sn->col = lastNode->col;
			break;
		case DIR_DEF::LEFT:
			sn->row = lastNode->row;
			sn->col = lastNode->col + 1;
			break;
		case DIR_DEF::RIGHT:
			sn->row = lastNode->row;
			sn->col = lastNode->col - 1;
			break;
		}
		this->allBody.pushBack(sn);
	}
}

