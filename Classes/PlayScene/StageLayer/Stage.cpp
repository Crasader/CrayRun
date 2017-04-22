/***************************************************************************
*|
*|	概要　スコアクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "Stage.h"


USING_NS_CC;
using namespace cocos2d::experimental;



bool Stage::init()
{
	if (!Node::init()) {

		return false;

	}


		s_Sorp = Sprite::create("Images/c.png");
		s_Sorp->setAnchorPoint(Vec2(0, 0));
		s_Sorp->setPosition(Vec2(200, 200));

		this->addChild(s_Sorp);
	return true;
}


