/***************************************************************************
*|
*|	概要　リザルトシーンの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/10
*|___________________________________________________________________________
****************************************************************************/

#pragma once

/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "../GameManager.h"

class ResultScene :public cocos2d::Scene
{
public:
	//シーンを作成する
	static cocos2d::Scene* create(int score, int distance);
	//初期化する
	 bool init(int score,int distance);

private:
	//タッチされたら
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent);
	////毎フレーム呼ばれる
	//void update(float data)override;


};