#include "WelcomeScene.h"
#include "GameScene.h"

WelcomeScene::WelcomeScene(void)
{
}


WelcomeScene::~WelcomeScene(void)
{
}
bool WelcomeScene::init(){
	if(!Scene::init())
		return false;
	WelcomeLayer *welcomeLayer=WelcomeLayer::create();
	this->addChild(welcomeLayer);
	return true;
}