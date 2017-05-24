#include "TitleScene.h"
#include "TitleLayer.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;

cocos2d::Scene * TitleScene::create()
{
	//メモリ確保
	TitleScene *pRet = new(std::nothrow)TitleScene();

	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}

}

bool TitleScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TitleScene::onTouchBegan, this);
	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	TitleLayer* titleLayer = TitleLayer::create();
	this->addChild(titleLayer);

	return true;
}

bool TitleScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent)
{
	return true;
}
