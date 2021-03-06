/***************************************************************************
*|
*|	概要　　ステージクラスの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- 多重インクルードの防止 ---------- */
#pragma once
/* ----  インクルード ---------- */
#include "cocos2d.h"
#include ".../../GameManager.h"

class Stage :public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(Stage);

private:

	std::vector < cocos2d::Vec2> m_FloorPos;//床座標


};


