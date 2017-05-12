/***************************************************************************
*|
*|	概要　　リザルトレイヤーの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/10
*|___________________________________________________________________________
****************************************************************************/

#pragma once 
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "ResultScore.h"



class ResultLayer :public cocos2d::Layer
{

public:
	virtual bool init();
	CREATE_FUNC(ResultLayer);
private:

	////毎フレーム呼び出される関数
	void update(float delta)override;
};


