/***************************************************************************
*|
*|	概要　　TitleSceneクラスの定義
*|　作成者　GF3 17 中田湧介
*|　作成日　2017/4/08
*|___________________________________________________________________________
****************************************************************************/

/* ---- ライブラリのインクルード ---------- */
#include "PlayScene.h"

USING_NS_CC;
using namespace cocos2d::experimental;

/* ---- メンバー関数の定義 ---------------- */
/***************************************************************************
*|	概要　　シーンを作成する。
*|	引数　　無し
*|　戻り値　シーンのアドレス
****************************************************************************/
cocos2d::Scene * PlayScene::createScene()
{
	// シーンを作成する

	auto scene = Scene::create();
	// レイヤーを作成する

	auto layer = PlayScene::create();
	// レイヤーをシーンに追加する

	scene->addChild(layer);
	// シーンを返す

	return scene;
}

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
	auto stagelayer = StageLayer::create();
	// ステージレイヤー関連のレイヤー
	this->addChild(stagelayer);
	// キャラクターレイヤー呼び出し
	auto characterlayer = CharacterLayer::create();
	// 背景レイヤー関連のレイヤ
	this->addChild(characterlayer);
	// UIレイヤー呼び出し
	auto uilayer = UiLayer::create();
	// UIレイヤー関連のレイヤ
	this->addChild(uilayer);



	


	return true;
}


