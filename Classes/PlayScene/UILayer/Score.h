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
#include "../../GameManager.h"


const int SCORE_MAX_NUMBER = 7;//スコアのスプライトの数



class Score :public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(Score);

	//スコアの設定、描画
	void ScoreIndicate(int Score);
private:
	//数字スプライト
	cocos2d::Sprite* s_Number[SCORE_MAX_NUMBER];

};

