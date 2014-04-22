//
//  GameLayer.cpp
//  Snake
//
//  Created by cookie on 14-4-13.
//
//

#include "GameLayer.h"



GameLayer::GameLayer()
{
   
}

GameLayer::~GameLayer()
{
    
}

Scene* GameLayer::GameScene(){
    Scene* gamescene = Scene::create();
    GameLayer* gamelayer = GameLayer::create();
    gamescene->addChild(gamelayer);
    return gamescene;
}

bool GameLayer::init(){
    bool bRect = false;
    
    do {
        ifgameover = false;
        SetApperance();
        SetSnake();
        SetFood();
        this->schedule(schedule_selector(GameLayer::update), 0.6);
        bRect = true;
    } while (0);
    
    return bRect;
}

void GameLayer::update(float dt){
    if (!HeadCollideBody(head->getDirec()) && !OutofRange()) {
         MoveStep();
        if(ifGetFood()){
            AddBody();
            SetFood();
        }
        lastbodyposi = body.at(body.size()-1)->getPosition();
    }
    else{
        GameOver();
    }
}

void GameLayer::SetApperance(){
    visiblesize = Director::getInstance()->getVisibleSize();
    
    background = Sprite::create("BackGround.png");
    background->setPosition(Point(visiblesize.width/2,visiblesize.height/2));
    this->addChild(background,0);  //this is the background
    
    butup = MenuItemImage::create("Button.png","Button2.png","Button.png",CC_CALLBACK_1(GameLayer::SetDirection,this,up));
    Size bs = butup->getContentSize();
    butup->setPosition(Point(visiblesize.width-3*bs.width+bs.width/2,3*bs.height+bs.height/2));

    butdown = MenuItemImage::create("Button.png","Button2.png","Button.png",CC_CALLBACK_1(GameLayer::SetDirection,this,down));
    butdown ->setPosition(Point(visiblesize.width-3*bs.width+bs.width/2,bs.height+bs.height/2));
    
    butleft = MenuItemImage::create("Button.png","Button2.png","Button.png",CC_CALLBACK_1(GameLayer::SetDirection,this,left));
    butleft ->setPosition(Point(visiblesize.width-4*bs.width+bs.width/2,2*bs.height+bs.height/2));
    
    butright = MenuItemImage::create("Button.png","Button2.png","Button.png",CC_CALLBACK_1(GameLayer::SetDirection,this,right));
    butright ->setPosition(Point(visiblesize.width-2*bs.width+bs.width/2,2*bs.height+bs.height/2));
    
    pausebutton = MenuItemImage::create("PauseButton.png","PauseButton.png",CC_CALLBACK_0(GameLayer::PauseGame,this));
    pausebutton->setPosition(Point(visiblesize.width - pausebutton->getContentSize().width,visiblesize.height - pausebutton->getContentSize().height/2));
    
    playbutton = MenuItemImage::create("rePlayButton1.png","rePlayButton2.png",CC_CALLBACK_0(GameLayer::StartGame, this));
    playbutton->setPosition(Point(visiblesize.width/2,visiblesize.height/2));
    playbutton->setVisible(false);
    
    menu = Menu::create(butup,butdown,butleft,butright,pausebutton,playbutton,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu,2);
    
    TTFConfig ttfconfig("Marker Felt.ttf",40);
    gameover = Label::createWithTTF(ttfconfig, " Game Over !",TextHAlignment::CENTER);
    gameover->setPosition(Point(visiblesize.width/2,visiblesize.height/2+gameover->getContentSize().height));
    gameover->setVisible(false);
    gameover->setColor(Color3B::BLACK);
    this->addChild(gameover,2);
    
    
    
}

void GameLayer::SetSnake(){
    body.clear();
    Size visiblesize = Director::getInstance()->getVisibleSize();
    head = SnakeHead::create();
    head->setNode(Sprite::create("SnakeHead.png"));
    head->setPosition(Point(visiblesize.width/2-head->getNode()->getContentSize().width/2,visiblesize.height/2-head->getNode()->getContentSize().height/2));
    this->addChild(head,1);
    
    for (int i=1 ; i < 4; i++) {
        Snake* bodynode = Snake::create();
        bodynode->setNode(Sprite::create("Snake.png"));
        bodynode->setPosition(Point(head->getPosition().x+i*bodynode->getNode()->getContentSize().width,head->getPosition().y));
        body.pushBack(bodynode);
        this->addChild(bodynode);
    }
    
}

void GameLayer::SetDirection(Ref* psender,Direction direc){
    Direction headdir = head->getDirec();
    if (movedflag && direc!= headdir) {
        switch (direc) {
            case up:
                if(headdir==left||headdir==right){
                    head->setDirec(up);
                }
                break;
            case down:
                if(headdir==left||headdir==right){
                    head->setDirec(down);
                }
                break;
            case left:
                if(headdir==up||headdir==down){
                    head->setDirec(left);
                }
                break;
            case right:
                if(headdir==up||headdir==down){
                    head->setDirec(right);
                }
                break;
            default:
                break;
        }
        movedflag = false;
    }else{
    
    }
    
    
}

void GameLayer::MoveStep(){
    movedflag = true;
    Direction temp = head->getDirec();
    Point po = head->Node::getPosition();
    switch (temp) {
        case up:
            //log("upupup");
            po.y += 20;
            break;
        case down:
            po.y -= 20;
            break;
        case left:
            po.x -= 20;
            break;
        case right:
            po.x += 20;
            break;
            
        default:
            break;
    }
    MoveBody();
    head->setPosition(po);
    
}

bool GameLayer::OutofRange(){
    Point po = head->getPosition();
    if (po.x < 0||po.x > visiblesize.width||po.y < 0||po.y > visiblesize.height) {
        return true;
    }
    return  false;
}

void GameLayer::MoveBody(){
    int n=body.size();
    Point HeadPosition = head->getPosition();
    Point a,temp;
    for (int i = 0; i < n; i++) {
        if(i==0){
            a = body.at(i)->getPosition();
            body.at(i)->setPosition(HeadPosition);
        }
        else {
            temp = a;
            a = body.at(i)->getPosition();
            body.at(i)->setPosition(temp);
         }
    }
    
}

bool GameLayer::HeadCollideBody(Direction headdirec){
    float x = head->getPosition().x;
    float y = head->getPosition().y;
    bool iscollide = false;
    switch (headdirec) {
        case up:
            y += 20;
            break;
        case down:
            y -= 20;
            break;
        case left:
            x -= 20;
            break;
        case right:
            x += 20;
            break;
        default:
            break;
    }
    Point headnextpos = Point (x,y);
    iscollide = ifCollideBody(headnextpos);
    return  iscollide;
}

void GameLayer::SetFood(){
    this->removeChild(food);
    Point foodposi = RandomPosition();
    Point headposi = head->getPosition();
    while (foodposi==headposi||ifCollideBody(foodposi)) {
        foodposi = RandomPosition();
    }
    food = Sprite::create("Food.png");
    food->setPosition(foodposi);
    this->addChild(food);
}

Point GameLayer::RandomPosition(){
    int x = (arc4random()%24);
    int y = (arc4random()%16);
    Point position = Point(x*20+10,y*20+10);
    return position;
}

bool GameLayer::ifCollideBody(Point pos){
    bool value = false;
    Snake* node;
    for (int i =0; i<body.size(); i++) {
        node = body.at(i);
        Point nodepos = node->getPosition();
        if(nodepos==pos){
            value = true;
        }
    }
    return value;
}

bool GameLayer::ifGetFood(){
    bool value = false;
    if(food->getPosition() == head->getPosition()){
        value = true;
    }
    return value;
}

void GameLayer::AddBody(){
    head->setPosition(food->getPosition());
    Snake* node = Snake::create();
    node->setNode(Sprite::create("Snake.png"));
    node->setPosition(lastbodyposi);
    body.pushBack(node);
    this->addChild(node);
}

void GameLayer::PauseGame(){
    
    this->pause();
    SetSnakeVisible(false);
    playbutton->setVisible(true);
    
}

void GameLayer::GameOver(){
    PauseGame();
    SetSnakeVisible(false);
    playbutton->setPosition(Point(visiblesize.width/2,visiblesize.height/2-gameover->getContentSize().height));
    gameover->setVisible(true);
    ifgameover = true;
}

void GameLayer::StartGame(){
    if(!ifgameover){
        SetSnakeVisible(true);
        this->resume();
    playbutton->setVisible(false);
    }else{
        this->unscheduleAllSelectors();
        this->removeAllChildren();
        //body.clear();
        this->init();
        
    }
}

void GameLayer::SetSnakeVisible(bool val){
    food->setVisible(val);
    head->getNode()->setVisible(val);
        for (int i =0; i<body.size(); i++) {
            body.at(i)->setVisible(val);
        }
}
























