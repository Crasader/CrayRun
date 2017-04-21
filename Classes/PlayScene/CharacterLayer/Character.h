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

class Character :public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(Character);

	void Move();//移動
	//virtual void Jump();//ジャンプする
	void Gravity();//重力
	//void Configuration();//設定
private:
	cocos2d::Sprite* s_player;

	//テスト斜面
	cocos2d::Sprite* s_Sorp;
};

