
/***************************************************************************
*|
*|	概要　リザルトシーンの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */

#include "EventListenerGesture.h"
#include "PauseScene.h"
#include "../PlayScene/PlayScene.h"
#include "../TitleScene/TitleScene.h"
/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;


bool PauseScene::init()
{
	// 親クラスを初期化する
	if (!Scene::init())
	{
		return false;
	}

	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(PauseScene::onTouchBegan, this);
	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	

	//つづけるボタンを作成する
	CountinueButton = ui::Button::create("Images/pause1.png");
	CountinueButton->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 2,450));
	this->addChild(CountinueButton);

	

	//タイトルボタンを作成する
	TitleButton = ui::Button::create("Images/pause2.png");
	TitleButton->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 2, 250));
	this->addChild(TitleButton);
	
	this->scheduleUpdate();

	return true;
}
void PauseScene::update(float data)
{

	if (CountinueButton->isHighlighted())
	{
		_director->popScene();
	}

	if (TitleButton->isHighlighted())
	{
		GameManager::Initialize();
		Scene* nextscene = TitleScene::create();
		_director->pushScene(nextscene);
	}
}
/* ---- メンバー関数の定義 ---------------- */

/***************************************************************************
*|	概要　　キーが押されたとき呼び出される関数
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
// タッチ開始時コールバック
bool PauseScene::onTouchBegan(Touch* touch, Event* pEvent)
{

	_director->popScene();


	return true;

}
