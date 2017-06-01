/***************************************************************************
*|
*|	概要　　背景クラスの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
#pragma once
/* ----  インクルード ---------- */
#include "cocos2d.h"




class Background :public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(Background);

	void update(float delta)override;

private:
	int sizeX;
	cocos2d::Sprite* background;
};



