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
	std::vector<cocos2d::Sprite*> crayfloor;
	//サイズ変更
	//void SetScale();
	//サイズ
	std::vector<cocos2d::Vec2>CrayStageSize;
private:
	//粘土床のカウント
	int CryFloorCnt;
	//今回の座標
	std::vector<cocos2d::Vec2> CrayStagePos;


};

