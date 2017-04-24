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

	//static Character* create();

	void Move();//移動
	virtual void Jump();//ジャンプする
	//重力
	void Character::Gravity()
	{
		if (GameManager::RightFlag == false)
		{
			GameManager::PlayerSpd.x = 6.0f;
		}
		GameManager::PlayerSpd.y -= 0.4f;
	}
	//void Configuration();//設定
	cocos2d::Sprite* s_player;
	//座標を取得する
	void GetPos() {
		GameManager::PlayerPos = s_player->getPosition();
	}
private:
	int F;
	float y_prev;
};

