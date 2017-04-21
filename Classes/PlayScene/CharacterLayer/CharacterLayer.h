/***************************************************************************
*|
*|	概要　　ResultLayer
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/

#pragma once 
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "GameManager.h"
#include "Character.h"
#include "Rabbit.h"

class CharacterLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(CharacterLayer);


private:
	//キャラクター
	Character* character;
	////毎フレーム呼び出される関数
	void update(float delta)override;

	//プレイヤーとステージのあたり判定
	//void AfterHittingStage();
	//プレイヤーと斜面のあたり判定
	void AfterHittingSlope();
	//プレイヤーとギミックのあたり判定
	//void AfterHittingGimmick();
	//プレイヤーと金型のあたり判定
	//void AfterHittingMold();
	//スケール計算
	//void ScaleCalculation();

};

