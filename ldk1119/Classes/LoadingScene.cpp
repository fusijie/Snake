#include "LoadingScene.h"
#include "WelcomeScene.h"


LoadingScene::LoadingScene(){}

LoadingScene::~LoadingScene(){}

bool LoadingScene::init() {
	if(Scene::init()){
		return true;
	} else {
		return false;
	}
}

void LoadingScene::onEnter(){
	// add background to current scene
	Sprite *background = Sprite::create("logo.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	background->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
	
	this->addChild(background);

	// start ansyc method load the atlas.png
	Director::getInstance()->getTextureCache()->addImageAsync("ui.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
}

void LoadingScene::loadingCallBack(Texture2D *texture){
	//载入纹理
	//AtlasLoader::getInstance()->loadAtlas("atlas.txt", texture);
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();

    cache->addSpriteFramesWithFile("ui.plist","ui.png");  
	//ResourceLoader* pLoader=ResourceLoader::getInstance();
	//pLoader->setSpriteFrameCache(cache);
	// After loading the texture , preload all the sound载入声音
	/*
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_die.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_hit.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_swooshing.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_wing.ogg");
	*/
	// After load all the things, change the scene to new one
	//auto scene = HelloWorld::createScene();
	//进入菜单场景
	auto scene = WelcomeScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}