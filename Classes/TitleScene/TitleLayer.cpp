#include "TitleLayer.h"
#include "../PlayScene/PlayScene.h"
#include "../InfoScene/InfoScene.h"
#include "../GameManager.h"

USING_NS_CC;

bool TitleLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	//背景スプライト
	Sprite* s_background = Sprite::create("Images/TitleBackground.png");
	s_background->setAnchorPoint(Vec2(0,0));
	this->addChild(s_background);

	//スタートボタン
	b_start = ui::Button::create("Images/StartImage.png");
	b_start->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 3, 200));
	this->addChild(b_start);

	//説明ボタン
	b_info = ui::Button::create("Images/InfoImage.png");
	b_info->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 3 * 1.5, 100));
	this->addChild(b_info);

	//終了ボタン
	b_exit = ui::Button::create("Images/ExitImage.png");
	b_exit->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 3 * 2, 200));
	this->addChild(b_exit);

	// Register Touch Event

	this->scheduleUpdate();
	return true;
}

void TitleLayer::update(float delta)
{
	//スタートボタンが押されたら
	if (b_start->isHighlighted())
	{
		GameManager::Initialize();
		Scene* nextscene = PlayScene::create();
		_director->pushScene(nextscene);
	}

	if (b_info->isHighlighted())
	{
		Scene* nextscene = InfoScene::create();
		_director->pushScene(nextscene);
	}

	//終了ボタンが押されたら
	if (b_exit->isHighlighted()) 
	{
		_director->end();
	}
}

