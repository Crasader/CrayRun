/***************************************************************************
*|
*|	概要　　スコアクラスの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
#pragma once
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "GameManager.h"
class CrayStage :public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(CrayStage);
	//粘土床
	cocos2d::Sprite* cryfloor;
	//サイズ変更
	void SetScale();
private:
	//粘土床のカウント
	int CryFloorCnt;
	//
	std::vector<cocos2d::Vec2> CrayStagePos;


};

