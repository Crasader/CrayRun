/***************************************************************************
*|
*|	概要　　UIレイヤーの定義
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

	//初期化
	m_distanceSpd = 0.18f;

	//レイヤーにノードを集約
    distance = Distance::create();
	this->addChild(distance);

	//レイヤーにノードを集約
	score = Score::create();
	this->addChild(score);


	this->scheduleUpdate();



	return true;


}



/***************************************************************************
*|	概要　　アップデート関数
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void UiLayer::update(float data) {
	//スコアを描画
	score->ScoreIndicate(GameManager::Score);

	//プレイヤーの速度xが正の時
	if (GameManager::PlayerSpd.x > 0.0f)
	{
		//距離を増やす
		distance->m_distance += m_distanceSpd;
		//距離を描画
		distance->DistanceIndicate(distance->m_distance);
	}

};