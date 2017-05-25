/***************************************************************************
*|
*|	概要　　プレイシーンクラスの定義
*|　作成者　GF3 17 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/

/* ---- ライブラリのインクルード ---------- */
#include "PlayScene.h"
/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

/* ---- メンバー関数の定義 ---------------- */
/***************************************************************************
*|	概要　　プレイシーンのレイヤーを呼びだす
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
bool PlayScene::init()
{
	// 親クラスを初期化する
	if (!Scene::init())
	{
		return false;
	}
	// 背景レイヤー呼び出し
	auto backgroundlayer = BackgroundLayer::create();
	// 背景レイヤー関連のレイヤー
	this->addChild(backgroundlayer);
	// ステージレイヤー呼び出し
	stagelayer = StageLayer::create();
	// ステージレイヤー関連のレイヤー
	this->addChild(stagelayer);
	// キャラクターレイヤー呼び出し
	characterlayer = CharacterLayer::create();
	// キャラクターレイヤー関連のレイヤ
	this->addChild(characterlayer);
	// UIレイヤー呼び出し
	uilayer = UiLayer::create();
	// UIレイヤー関連のレイヤ
	this->addChild(uilayer);

	//カメラを作成する
	Camera* camera = Camera::create();
	camera->setCameraFlag(CameraFlag::USER1);
	this->addChild(camera);


	//// 一時停止
	//cocos2d::Director::getInstance()->pause();
	//cocos2d::Director::getInstance()->isPaused();


	//マップ画像生成
	for (int i = 1; i <= 3; i++)
	{
		std::ostringstream MapName;
		MapName<< "Images/" << i << ".png";
		Number[i-1] = Sprite::create(MapName.str());
		Number[i-1]->setPosition(GameManager::SCREEN_SIZE / 2);
		Number[i-1]->setVisible(false);
		this->addChild(Number[i-1]);
	}

	//GO画像生成
	Go = Sprite::create("Images/GO.png");
	Go->setPosition(GameManager::SCREEN_SIZE / 2);
	Go->setVisible(false);
	this->addChild(Go);

	
	//update関数を呼ぶ
	this->scheduleUpdate();

	return true;
}

/***************************************************************************
*|	概要　　毎フレーム呼ばれる
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void PlayScene::update(float data)
{

	if (StopFlag == false)
	{
		StopFlag = true;
		//カウントダウンをする
		NumberAction(3);
		//キャラクタレイヤを止める
		characterlayer->pause();
		//UIレイヤを止める
		uilayer->pause();
		//ステージレイヤを止める
		stagelayer->pause();
	}

	if (m_CameraFlag == true)
	{
		//デフォルトカメラを設定する
		PlayScene::m_camera = this->getDefaultCamera();
		//カメラ座標を、毎フレーム動かす
		GameManager::m_cameraposx += GameManager::m_cameraspdx;
		GameManager::WorldPosX += GameManager::m_cameraspdx;
		//カメラの座標をセット
		PlayScene::m_camera->setPositionX(GameManager::m_cameraposx);

		//UI専用のカメラにする
		uilayer->setCameraMask((unsigned short)CameraFlag::USER1);
	}


	//画面左もしくは画面下に出たらリザルトシーンへ移行
	if (GameManager::PlayerPos.y < 0 ||  GameManager::PlayerPos.x <= GameManager::WorldPosX || GameManager::GameOverFlag == true)
	{

		//キャラクタレイヤを止める
		characterlayer->pause();
		//UIレイヤを止める
		uilayer->pause();
		//ステージレイヤを止める
		//カメラを止める
		m_CameraFlag = false;
		//ポーズ機能使用不可に
		GameManager::CountDownFlag = false;

		//エフェクト生成
		Effect = Sprite::create("Images/EndEffect.png");
		Effect->setPosition(GameManager::PlayerPos.x + GameManager::PlayerSize.x, GameManager::PlayerPos.y + GameManager::PlayerSize.y / 2);
		this->addChild(Effect);

		//少し止めてからシーン以降
		DelayTime* action = DelayTime::create(1.0f);
		CallFunc* action2 = CallFunc::create(CC_CALLBACK_0(PlayScene::TransitionPlayToResult, this));
		Sequence* action3 = Sequence::create(action, action2, nullptr);
		this->runAction(action3);
	}

}


//数字のアクション再起関数
void PlayScene::NumberAction(int cnt)
{
	//待つ、表示、動く、消える、関数呼ぶを順番に
	DelayTime* action = DelayTime::create(0.5f);
	Show* action2 = Show::create();
	MoveBy* action3 = MoveBy::create(0.4f, Vec2(0.0f, -50.0f));
	RemoveSelf* action4 = RemoveSelf::create();
	CallFunc* action5 = CallFunc::create(CC_CALLBACK_0(PlayScene::NumberAction, this, --cnt));
	Sequence* action6 = Sequence::create(action, action2, action3, action4, action5,  nullptr);
	
	//Goのアクションとして実行
	if (cnt == -1)
	{
		Go->runAction(action6);
	}
	
	//全て終わったらカメラを動かす
	else if (cnt == -2)
	{
		//カメラを動かす
		m_CameraFlag = true;
		//キャラクタレイヤを再始動する
		characterlayer->resume();
		//UIレイヤを再始動する
		uilayer->resume();
		//ステージの再始動する
		stagelayer->resume();
		//ポーズ機能ができるようにする
		GameManager::CountDownFlag = true;
	}
	//カウントとしてアクションを実行
	
	if (cnt >= 0)
	{
		Number[cnt]->runAction(action6);
	}
}


