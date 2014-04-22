//
//  GameLayer.cpp
//  Snake
//
//  Created by fireblackill on 14-4-10.
//
//

#include "GameLayer.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* GameLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = GameLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    auto labelBack = Label::create("MainMenu", "宋体", 24);
    auto uiBack = MenuItemLabel::create(labelBack, CC_CALLBACK_1(GameLayer::menuBackToMain, this));
    uiBack->setPosition(Point(900,200));
    
    auto menu = Menu::create(uiBack, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    m_head = new SnakeNode();
    m_head->row = arc4random()%10;
    m_head->col = arc4random()%10;

    m_food = new SnakeNode();
    m_food->row = arc4random()%10;
    m_head->col = arc4random()%10;
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    this->schedule(schedule_selector(GameLayer::update), 0.5);
    
    return true;
}

void GameLayer::draw(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    //绘制直线
    glLineWidth(4);
    for (int i = 0; i<11; i++)
    {
        DrawPrimitives::drawLine(Point(0,i*64), Point(640,i*64));
        DrawPrimitives::drawLine(Point(i*64,0), Point(i*64,640));
    }
    
    //绘制蛇头
    DrawPrimitives::drawSolidRect(Point(m_head->col * 64 , m_head->row * 64 ),
                                  Point(m_head->col * 64 +64,m_head->row * 64 +64),
                                  Color4F(1.0f,0,0,1.0f));
    
    //绘制蛋
    DrawPrimitives::drawSolidRect(Point(m_food->col * 64 , m_food->row * 64 ),
                                  Point(m_food->col * 64 +64,m_food->row * 64 +64),
                                  Color4F(0,0,1.0f,1.0f));
    
    //绘制蛇身
    for(auto &sn : m_body)
    {
        DrawPrimitives::drawSolidRect(Point(sn->col * 64, sn->row * 64),
                                      Point(sn->col * 64 + 64, sn->row * 64 +64),
                                      Color4F(0,0,1.0f,1.0f));
    }
    
    Layer::draw(renderer, transform, transformUpdated);
}

void GameLayer::update(float dt)
{
    //蛇身每一段跟随前一段移动
    for(int i = m_body.size() -1 ;i>=0;i--)
    {
        SnakeNode* sn = m_body.at(i);
        
        if(i!=0)
        {
            SnakeNode* pre = m_body.at(i-1);
            sn->dir = pre->dir;
            sn->col = pre->col;
            sn->row = pre->row;
        }
        else
        {
            sn->dir = m_head->dir;
            sn->col = m_head->col;
            sn->row = m_head->row;
        }
    }
    
    //根据方向来让蛇头移动
    switch (m_head->dir)
    {
        case UP:
            m_head->row++;
            log("up");
            if(m_head->row >=10) m_head->row = 0;
            break;
        case DOWN:
            m_head->row--;
            log("down");
            if(m_head->row <0) m_head->row = 9;
            break;
        case RIGHT:
            m_head->col++;
            if(m_head->col >=10) m_head->col = 0;
            break;
        case LEFT:
            m_head->col--;
            if(m_head->col < 0) m_head->col = 9;
            break;
        default:
            break;
    }
    
    //和蛋的碰撞检测
    if(m_head->row == m_food->row && m_head->col == m_food->col)
    {
        //刷新蛋
        m_food->row = arc4random()%10;
        m_food->col = arc4random()%10;
        
        //设置新的尾巴的参数
        SnakeNode* sn = new SnakeNode();
        SnakeNode* last = NULL;
        if(m_body.size() > 0)
        {
            last = m_body.back();
        }
        else
        {
            last = m_head;
        }
        
        switch (last->dir)
        {
            case UP:
                sn->row = last->row - 1;
                sn->col = last->col;
                break;
            case DOWN:
                sn->row = last->row + 1;
                sn->col = last->col;
                break;
            case LEFT:
                sn->row = last->row;
                sn->col = last->col + 1;
                break;
            case RIGHT:
                sn->row = last->row;
                sn->col = last->col - 1;
                break;
                
            default:
                break;
        }
        //添加进身体的Vector中
        m_body.pushBack(sn);
    }
}

void GameLayer::menuBackToMain(cocos2d::Ref *pSender)
{
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

bool GameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Point tPos = touch->getLocation();
    int nowRow = ((int)tPos.y)/64;
    int nowCol = ((int)tPos.x)/64;
    
    if(abs(nowRow - m_head->row) > abs(nowCol - m_head->col))
    {
        //上下移动
        if(nowRow > m_head->row)
        {
            m_head->dir  = UP;
        }
        else
        {
            m_head->dir  = DOWN;
        }
    }
    else
    {
        //左右移动
        if(nowCol > m_head->col)
        {
            m_head->dir = RIGHT;
        }
        else
        {
            m_head->dir = LEFT;
        }
    }
    
    return true;
}