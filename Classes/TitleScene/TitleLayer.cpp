#include "TitleLayer.h"
#include "../PlayScene/PlayScene.h"
#include "../GameManager.h"

USING_NS_CC;

bool TitleLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	Sprite* s_background = Sprite::create("Images/TitleBackground.png");
	s_background->setAnchorPoint(Vec2(0,0));
	this->addChild(s_background);

	// Register Touch Event
	EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(TitleLayer::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(TitleLayer::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(TitleLayer::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(TitleLayer::onTouchesCancelled, this);

	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();
	return true;
}

void TitleLayer::update(float delta)
{
}

void TitleLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
}

void TitleLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
}

void TitleLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	GameManager::Initialize();

	auto nextScene = PlayScene::create();
	// run
	log("############################### PlayScene created");
	_director->replaceScene(nextScene);

}

void TitleLayer::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
}