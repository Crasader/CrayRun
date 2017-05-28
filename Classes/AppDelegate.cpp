#include "AppDelegate.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "SimpleAudioEngine.h"
#include "TitleScene/TitleScene.h"


USING_NS_CC;

using namespace CocosDenshion;
using namespace experimental;



AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {


	/* 乱数系列の変更 */
	srand((unsigned)time(NULL));
	//音楽ファイルを読み込み
	AudioEngine::preload("Sounds/domovoice.mp3");
	AudioEngine::preload("Sounds/RabbitVoice.mp3");
	AudioEngine::preload("Sounds/Gnome_VoiceSE.mp3");
	AudioEngine::preload("Sounds/phoenix_CrySE.mp3");
	AudioEngine::preload("Sounds/SlimeSE.mp3");
	AudioEngine::preload("Sounds/jump04.ogg");
	AudioEngine::preload("Sounds/ResultBGM.ogg");
	AudioEngine::preload("Sounds/coin03.mp3");
	AudioEngine::preload("Sounds/TitleBGMLoop.mp3");
	AudioEngine::preload("Sounds/crash.mp3");

	//AudioEngine::preload("Sounds/");


	log("############################### AppDelegate started");
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("CrayRun", Rect(0, 0, 960, 640));
        director->setOpenGLView(glview);
    }
    director->getOpenGLView()->setDesignResolutionSize(960, 640, ResolutionPolicy::SHOW_ALL);

	// turn on display FPS
  //  director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);
	log("############################### glview created");

    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object


	auto scene = TitleScene::create();
    // run
	log("############################### PlayScene created");
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    //Director::getInstance()->stopAnimation();

    //// if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
     SimpleAudioEngine::getInstance()->resumeBackgroundMusic();


}



