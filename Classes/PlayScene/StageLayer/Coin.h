/***************************************************************************
*|
*|	概要　　コインクラスの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
#pragma once
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"

class Coin :public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(Coin);
	cocos2d::Sprite* s_Coin;//コイン
	
private:


};

