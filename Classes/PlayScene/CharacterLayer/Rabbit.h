/***************************************************************************
*|
*|	概要　　ウサギクラスの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- 多重インクルードの防止 ---------- */
#pragma once
/* ----  インクルード ---------- */
#include "cocos2d.h"
#include "Character.h"


class Rabbit :public Character
{
public:
	bool init();
	CREATE_FUNC(Rabbit);

	void Animation();

private:

	const float JUMPSIZE = 13.0f;
	const float SCORECORRECTION = 1.2f;

};