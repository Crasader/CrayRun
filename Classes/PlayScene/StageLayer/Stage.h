/***************************************************************************
*|
*|	概要　　スコアクラスの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
#pragma once
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "GameManager.h"

class Stage :public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(Stage);
		static float* FloorPosx[];//床座標x
	static float* FloorPosy[];//床座標y
private:

	//テスト斜面
	cocos2d::Sprite* s_Sorp;

};


