/***************************************************************************
*|
*|	概要　　ステータスクラスを宣言する
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/6/1
*|___________________________________________________________________________
****************************************************************************/

/* ---- 多重インクルードの防止 ---------- */
#pragma once
/* ----  インクルード ---------- */
#include "cocos2d.h"
#include "GameManager.h"

class Status : public cocos2d::Node
{
public:

	virtual bool init();

	CREATE_FUNC(Status);

	////毎フレーム呼び出される関数
	void update(float delta)override;

	//スプライトを作成する関数
	void StatusAction();
private:

	//ステータスのスプライト
	cocos2d::Sprite* s_status[GameManager::MaxCharacterKind];


};