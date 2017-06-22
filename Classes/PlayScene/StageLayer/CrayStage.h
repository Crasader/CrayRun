/***************************************************************************
*|
*|	概要　　スコアクラスの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- 多重インクルードの防止 ---------- */
#pragma once
/* ----  インクルード ---------- */
#include "cocos2d.h"
#include "GameManager.h"
#include "CrayStageSprite.h"

class CrayStage :public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(CrayStage);
	//サイズ変更
	//void SetScale();
	//粘土床
	std::vector<CrayStageSprite*> m_crayfloor;
private:
	
	//今回の座標
	std::vector<cocos2d::Vec2> CrayStagePos;


};

