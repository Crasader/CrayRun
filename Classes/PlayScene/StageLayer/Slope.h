/***************************************************************************
*|
*|	概要　　斜面クラスの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
#pragma once
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"
class Slope :public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(Slope);

private:
	//斜面幅
	cocos2d::Vec2 SlopeSize;
	//斜面スプライト
	cocos2d::Sprite* s_slope;
	//イテレータ
	cocos2d::Vector<cocos2d::Vec2>::iterator IteratorRight;
	cocos2d::Vector<cocos2d::Vec2>::iterator IteratorLeft;

	//登り
	bool ClimbingFlag;


	//イテレータの値を格納する
	cocos2d::Vec2 SaveRight;
	cocos2d::Vec2 SaveLeft;


};
