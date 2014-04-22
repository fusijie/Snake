#include "GameScene.h"
#include "BackgroundLayer.h"
#include "GameLayer.h"
#include "StatusLayer.h"
GameScene::GameScene(void)
{
}


GameScene::~GameScene(void)
{
}
bool GameScene::init(){
	if(!Scene::init())
		return false;
	auto *backgroundLayer=BackgroundLayer::create();
	this->addChild(backgroundLayer);
	auto *gameLayer=GameLayer::create();
	auto *statusLayer=StatusLayer::create();
	gameLayer->setDelegator(statusLayer);
	
	this->addChild(gameLayer);
	this->addChild(statusLayer);
	return true;
}
