/// <summary>
/// 概　要：ステータスの定義
/// 作成者：GS2 24 山本悠雅
/// 作成日：2017/05/15
/// </summary>
#pragma once
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "GameManager.h"

class Status : public cocos2d::Node
{
public:

	virtual bool init();
	
	CREATE_FUNC(Status);

	////毎フレーム呼び出される関数
	void update(float delta)override;

private:

	//ステータスのスプライト
	cocos2d::Sprite* s_status;

	//カウント
	int m_cnt;

	//スプライトを作成する関数
	void CreateSprite();
};