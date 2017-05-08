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

};