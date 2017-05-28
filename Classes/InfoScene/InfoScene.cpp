#include "InfoScene.h"
#include "../TitleScene/TitleScene.h"
#include "../GameManager.h"
#include "audio/include/AudioEngine.h"
/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
//using namespace experimental;

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
	Infomation[3] = Sprite::create("Images/Infomation/Info4.png");
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

	page = 1;
	pageCnt = 0;

	this->scheduleUpdate();

	return true;
}

void InfoScene::update(float delta)
{
	if (b_BackScene->isHighlighted())
	{
		experimental::AudioEngine::play2d("Sounds/touch.mp3");
		Scene* nextscene = TitleScene::create();
		_director->pushScene(nextscene);
	}

	switch (page)
	{

	case 2:

		if (pageCnt % 10 == 0)
		{
			Texture2D* texture;
			switch (pageCnt / 10 % 2)
			{
			case 0:
				texture = TextureCache::sharedTextureCache()->addImage("Images/Infomation/Info2.png");

				Infomation[page - 1]->setTexture(texture);
				break;
			case 1:
				texture = TextureCache::sharedTextureCache()->addImage("Images/Infomation/Info2_1.png");

				Infomation[page - 1]->setTexture(texture);
				break;
			}
		}

		pageCnt++;
		break;
	case 3:
		if (pageCnt % 10 == 0)
		{
			Texture2D* texture;
			switch (pageCnt / 10 % 2)
			{
			case 0:
				texture = TextureCache::sharedTextureCache()->addImage("Images/Infomation/Info3.png");

				Infomation[page - 1]->setTexture(texture);
				break;
			case 1:
				texture = TextureCache::sharedTextureCache()->addImage("Images/Infomation/Info3_1.png");

				Infomation[page - 1]->setTexture(texture);
				break;
			}
		}

		pageCnt++;
		break;

	case 4:
		if (pageCnt % 10 == 0)
		{
			Texture2D* texture;
			switch (pageCnt / 10 % 2)
			{
			case 0:
				texture = TextureCache::sharedTextureCache()->addImage("Images/Infomation/Info4.png");

				Infomation[page - 1]->setTexture(texture);
				break;
			case 1:
				texture = TextureCache::sharedTextureCache()->addImage("Images/Infomation/Info4_1.png");

				Infomation[page - 1]->setTexture(texture);
				break;
			}
		}

		pageCnt++;
		break;
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
		if (page != MAX_INFOMATION_PASE)
		{
			if (Infomation[0]->numberOfRunningActions() == 0)
			{
				page++;
				pageCnt = 0;
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
			if (page != 1)
			{
				if (Infomation[0]->numberOfRunningActions() == 0)
				{
					page--;
					pageCnt = 0;
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
