/***************************************************************************
*|
*|	概要　　リザルトレイヤー
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "StageLayer.h"

USING_NS_CC;

bool StageLayer::init()
{
	if (!Layer::init()) {

		return false;

	}

	//レイヤーにノードを集約
	Coin* coin = Coin::create();
	this->addChild(coin);

	//レイヤーにノードを集約
	CrayStage* craystage = CrayStage::create();
	this->addChild(craystage);


	//レイヤーにノードを集約
	Stage* stage = Stage::create();
	this->addChild(stage);



	this->scheduleUpdate();


	return true;

}



void StageLayer::update(float data) {};