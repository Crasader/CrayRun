
/***************************************************************************
*|
*|	概要　リザルトシーンの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "EventListenerGesture.h"
#include "PauseScene.h"
#include "../PlayScene/PlayScene.h"
#include "../TitleScene/TitleScene.h"
#include "audio/include/AudioEngine.h"
/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
//using namespace experimental;

/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
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
		experimental::AudioEngine::play2d("Sounds/touch.mp3");
		_director->popScene();
	}

	if (TitleButton->isHighlighted())
	{
		//プレイシーンのBGM終了
		experimental::AudioEngine::stop(PlayScene::PlayBgm);
		experimental::AudioEngine::play2d("Sounds/touch.mp3");

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
