#include "InfoScene.h"
#include "../TitleScene/TitleScene.h"
#include "../GameManager.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;


cocos2d::Scene * InfoScene::create()
{
	//メモリ確保
	InfoScene *pRet = new(std::nothrow)InfoScene();

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

bool InfoScene::init()
{
	if (!Scene::init()) {
		return false;
	}
	Infomation[0] = Sprite::create("Images/Infomation/Info1.png");
	Infomation[1] = Sprite::create("Images/Infomation/Info2.png");
	Infomation[2] = Sprite::create("Images/Infomation/Info3.png");
	for (int i = 0; i < MAX_INFOMATION_PASE; i++)
	{
		Infomation[i]->setAnchorPoint(Vec2(0,0));
		Infomation[i]->setPosition(Vec2(i * GameManager::SCREEN_SIZE.x, 0));
		this->addChild(Infomation[i]);
	}

	b_Next = ui::Button::create("Images/InfoNext.png");
	b_Next->setPosition(Vec2(GameManager::SCREEN_SIZE.x - GameManager::SCREEN_SIZE.x / 5, 100));
	this->addChild(b_Next);

	b_Back = ui::Button::create("Images/InfoBack.png");
	b_Back->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 5, 100));
	this->addChild(b_Back);

	b_BackScene = ui::Button::create("Images/InfoBackScene.png");
	b_BackScene->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 2, 100));
	this->addChild(b_BackScene);

	b_Next->addTouchEventListener(CC_CALLBACK_2(InfoScene::OnButtonTouchNext, this));
	b_Back->addTouchEventListener(CC_CALLBACK_2(InfoScene::OnButtonTouchBack, this));

	pase = 1;

	this->scheduleUpdate();

	return true;
}

void InfoScene::update(float delta)
{
	if (b_BackScene->isHighlighted())
	{
		Scene* nextscene = TitleScene::create();
		_director->pushScene(nextscene);
	}
}

void InfoScene::OnButtonTouchNext(Ref * ref, ui::Widget::TouchEventType eventtype)
{
	switch (eventtype)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED:
		//ページが最後のページになっていない場合
		if (pase != MAX_INFOMATION_PASE)
		{
			if (Infomation[0]->numberOfRunningActions() == 0)
			{
				pase++;

				for (int i = 0; i < MAX_INFOMATION_PASE; i++)
				{
					MoveBy* ActionMove = MoveBy::create(1.0f, Vec2(-GameManager::SCREEN_SIZE.x, 0));
					Infomation[i]->runAction(ActionMove);
				}
			}
		}
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void InfoScene::OnButtonTouchBack(Ref * ref, ui::Widget::TouchEventType eventtype)
{
	switch (eventtype)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED:
			//ページが最初のページになっていない場合
			if (pase != 1)
			{
				if (Infomation[0]->numberOfRunningActions() == 0)
				{
					pase--;
					for (int i = 0; i < MAX_INFOMATION_PASE; i++)
					{
						MoveBy* ActionMove = MoveBy::create(1.0f, Vec2(GameManager::SCREEN_SIZE.x, 0));
						Infomation[i]->runAction(ActionMove);
					}
				}
			}
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
