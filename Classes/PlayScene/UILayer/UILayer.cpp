/***************************************************************************
*|
*|	概要　　リザルトレイヤー
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "UiLayer.h"

USING_NS_CC;

bool UiLayer::init()
{
	if (!Layer::init()) {

		return false;

	}

	//レイヤーにノードを集約
	Distance * distance = Distance::create();
	this->addChild(distance);

	//レイヤーにノードを集約
	Score* score = Score::create();
	this->addChild(score);

	this->scheduleUpdate();


	return true;


}



void UiLayer::update(float data) {};