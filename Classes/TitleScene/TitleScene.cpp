#include "TitleScene.h"
#include "TitleLayer.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;

cocos2d::Scene * TitleScene::create()
{
	//�������m��
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

	// �^�b�`�C�x���g���X�i�[���쐬
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
