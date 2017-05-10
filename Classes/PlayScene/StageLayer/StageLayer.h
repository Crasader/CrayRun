/***************************************************************************
*|
*|	概要　　ステージレイヤーの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/

#pragma once 
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "Coin.h"
#include "RabbitMold.h"
#include "CrayStage.h"
#include "Stage.h"
#include "Slope.h"

class StageLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(StageLayer);


private:

	////毎フレーム呼び出される関数
	void update(float delta)override;
	//プレイヤーとコインの当たり判定後
	void CollisionResponseCoin();
	//プレイヤと金型のあたり判定
	void HittingMold();
	//金型と床のあたり判定
	void HittingFloorToMold();

	RabbitMold* Rmold;
	//Slope* slope;
	Stage* stage;
	//コイン
	std::vector<Coin*> coin;
	//コインイテレータ
	cocos2d::Vector<Coin*>::iterator IteratorCoin;
	
};


