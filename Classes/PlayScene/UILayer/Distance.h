/***************************************************************************
*|
*|	概要　　距離クラスの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
#pragma once
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include"../../GameManager.h"

const int DISTANCE_MAX_NUMBER = 10;//距離のスプライトの数

class Distance :public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(Distance);

	//距離の設定、描画
	void DistanceIndicate(int distance);

	float m_distance;//

private:
	//数字スプライト
	cocos2d::Sprite* s_Number[DISTANCE_MAX_NUMBER];
	int Digit;//桁数
	int SpriteCnt;//何個目のスプライトかカウントする
	int DistanceMaxDigit;//最大桁数
	 //メートルスプライト
	cocos2d::Sprite* M;
};

