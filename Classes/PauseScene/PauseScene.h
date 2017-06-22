/***************************************************************************
*|
*|	概要　リザルトシーンの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ---- 多重インクルードの防止 ---------- */
#pragma once

/* ----  インクルード ---------- */
#include "cocos2d.h"
#include "../GameManager.h"
#include "ui/CocosGUI.h"

class PauseScene :public cocos2d::Scene
{
public:

	//初期化する
	bool init();
	CREATE_FUNC(PauseScene);

private:
	//タッチされたら
	//bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent);
	////毎フレーム呼ばれる
	void update(float data)override;
	cocos2d::ui::Button* CountinueButton;//ボタン
	cocos2d::ui::Button* TitleButton;//ボタン
};