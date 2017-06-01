/***************************************************************************
*|
*|	概要　　背景レイヤークラス
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/

/* ---- 多重インクルードの防止 ---------- */
#pragma once 
/* ----  インクルード ---------- */
#include "cocos2d.h"
#include "Background.h"

class BackgroundLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(BackgroundLayer);


private:
	Background* background;
	////毎フレーム呼び出される関数
	void update(float delta)override;

};

