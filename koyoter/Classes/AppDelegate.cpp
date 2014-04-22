#include "AppDelegate.h"
#include "MenuScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Snake Game");
		log("Snake Game");
#if (CC_TARGET_PLATFORM == OS_WINDOWS)
		glview->setFrameSize( 960 , 640 );
#endif
        director->setOpenGLView(glview);
    }

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
	Size frameSize = glview->getFrameSize();
	float designWidth,designHeight;
	if (frameSize.width / frameSize.height > 960 / 640)
	{
		designHeight = 640;
		designWidth = frameSize.width / ( frameSize.height  / designHeight);
	}
	else
	{
		designWidth = 960;
		designHeight = frameSize.height / (frameSize.width / designWidth);
	}
	glview->setDesignResolutionSize(designWidth , designHeight , ResolutionPolicy::NO_BORDER );
    
	auto scene = MenuScene::createScene();
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
