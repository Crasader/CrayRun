/***************************************************************************
*|
*|	概要　　プレイシーンクラスの宣言
*|　作成者　GF3 17 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
#pragma once

/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "StageLayer/StageLayer.h"
#include "BackgroundLayer/BackgroundLayer.h"
#include "CharacterLayer/CharacterLayer.h"
#include "UILayer/UILayer.h"
#include "../GameManager.h"
#include "../ResultScene/ResultScene.h"
#include "ui/CocosGUI.h"
class PlayScene :public cocos2d::Scene
{
public:
	//シーンを作成する
	//static cocos2d::Scene* createScene();
	
	CREATE_FUNC(PlayScene);
	//初期化する
	virtual bool init();

private:
	//毎フレーム呼ばれる
	void update(float data)override;
	cocos2d::Camera* m_camera;
	cocos2d::Layer* uilayer;

	//3.2.1のスプライト
	cocos2d::Sprite* Number[3];
	//数字のアクション
	void NumberAction(int cnt);
	//Goのスプライト
	cocos2d::Sprite* Go;
	//キャラクタレイヤ
	CharacterLayer* characterlayer;
	//カメラフラグ
	bool m_CameraFlag;
	//止めるかどうか
	bool StopFlag;
	//リザルトシーンへ
	void TransitionPlayToResult() {
		cocos2d::Scene* nextScene = ResultScene::create(GameManager::Score, GameManager::TotalDistance);
		_director->replaceScene(nextScene);
	}
	//エフェクト
	cocos2d::Sprite* Effect;

	//ステージ
	StageLayer* stagelayer;



};