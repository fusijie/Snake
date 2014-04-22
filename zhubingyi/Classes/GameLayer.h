//
//  GameLayer.h
//  Snake
//
//  Created by cookie on 14-4-13.
//
//

#ifndef __Snake__GameLayer__
#define __Snake__GameLayer__

#include <iostream>
#include "cocos2d.h"
#include "SnakeHead.h"

USING_NS_CC;

class GameLayer : public Layer{

public:
    GameLayer(void);
    ~GameLayer(void);
    virtual bool init();
    virtual void update(float dt);
    CREATE_FUNC(GameLayer);
    
    void SetApperance();
    void SetSnake();
    void SetDirection(Ref* psender,Direction direc);
    void MoveStep();
    bool OutofRange();
    bool HeadCollideBody(Direction headdirec);
    void MoveBody();
    void SetFood();
    Point RandomPosition();
    bool ifCollideBody(Point pos);
    bool ifGetFood();
    void AddBody();
    void SetGameScore(int gs);
    static Scene* GameScene();
    void PauseGame();
    void GameOver();
    void StartGame();
    void SetSnakeVisible(bool value);
    
private:
    SnakeHead* head;
    Vector<Snake*> body;
    Sprite* background;
    Sprite* food;
    MenuItemImage* butup;
    MenuItemImage* butdown;
    MenuItemImage* butleft;
    MenuItemImage* butright;
    MenuItemImage* pausebutton;
    MenuItemImage* playbutton;
    Menu* menu;
    Label* gameover;
    bool ifgameover;
    Point lastbodyposi;
    Size visiblesize;
    bool movedflag;
    
    
    
    
    
};


#endif /* defined(__Snake__GameLayer__) */
