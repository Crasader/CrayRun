/***************************************************************************
*|
*|	概要　　ウサギクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
#pragma once
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "Character.h"


class Rabbit :public Character
{
public:
	bool init();
	CREATE_FUNC(Rabbit);

	void Move();

private:


};