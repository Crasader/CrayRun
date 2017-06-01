/***************************************************************************
*|
*|	概要　　タイトルレイヤクラスを定義する
*|　作成者　GS2 16 中田湧介
*|　作成日　2017//
*|___________________________________________________________________________
****************************************************************************/
/* ---- インクルード ---------- */
#include "TitleLayer.h"
#include "../PlayScene/PlayScene.h"
#include "../InfoScene/InfoScene.h"
#include "../GameManager.h"
#include "TitleCharacter.h"
#include "audio\include\AudioEngine.h"
/* ---- 多重インクルードの防止 ---------- */
USING_NS_CC;


/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
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
	b_start->setScale(0.8, 0.8);
	this->addChild(b_start);

	//説明ボタン
	b_info = ui::Button::create("Images/InfoImage.png");
	b_info->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 3 * 1.5, 100));
	b_info->setScale(0.8, 0.8);
	this->addChild(b_info);

	//終了ボタン
	b_exit = ui::Button::create("Images/ExitImage.png");
	b_exit->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 3 * 2, 200));
	b_exit->setScale(0.8, 0.8);
	this->addChild(b_exit);

	//タイトルキャラクタの作成
	TitleChracter* titlecharacter = TitleChracter::create();
	this->addChild(titlecharacter);

	//////音声を再生をする
	TitleBgm = experimental::AudioEngine::play2d("Sounds/TitleBGMLoop.ogg",true);
	//experimental::AudioEngine::setLoop(TitleBgm,true);
	//音楽オブジェクト生成


	this->scheduleUpdate();
	return true;
}


void TitleLayer::update(float delta)
{
	//スタートボタンが押されたら
	if (b_start->isHighlighted())
	{
		//音楽止める
		experimental::AudioEngine::stop(TitleBgm);
		experimental::AudioEngine::play2d("Sounds/touch.mp3");
		//音声を再生をする
		//experimental::AudioEngine::setFinishCallback(touchAudio,CC_CALLBACK_0(TitleLayer::IsuncacheAll,this));


		//初期化処理
		GameManager::Initialize();

		////プレイシーンへ
		Scene* nextscene = PlayScene::create();
		_director->pushScene(nextscene);
	
	}
	//説明書
	if (b_info->isHighlighted())
	{

		//BGMを止める
		experimental::AudioEngine::stop(TitleBgm);
		experimental::AudioEngine::play2d("Sounds/touch.mp3");

		//音声キャッシュ
	//	experimental::AudioEngine::uncacheAll();
		Scene* nextscene = InfoScene::create();
		_director->pushScene(nextscene);
	}

	//終了ボタンが押されたら
	if (b_exit->isHighlighted()) 
	{
		
		experimental::AudioEngine::play2d("Sounds/touch.mp3");

		_director->end();
	}
}

