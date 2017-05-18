/***************************************************************************
*|
*|	概要　　敵クラスの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/17
*|___________________________________________________________________________
****************************************************************************/
#pragma once
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include ".../../GameManager.h"

class Enemy :public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(Enemy);
	std::vector < cocos2d::Vec2> m_EnemyPos;//床座標

private:



};


#pragma once
