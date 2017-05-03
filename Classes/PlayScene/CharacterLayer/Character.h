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
	virtual void Jump();//ジャンプする
	//重力
	void Gravity()
	{
		if (GameManager::RightFlag == false)
		{
			GameManager::PlayerSpd.x = 6.0f;
		}
		//重力加速度に上限を設ける
		if (GameManager::PlayerSpd.y >= -4.5f)
		{
			GameManager::PlayerSpd.y -= 0.4f;
		}
		//ジャンプがないときは関係なく加速度をつける
		else if (GameManager::JumpFlag == false)
		{
			GameManager::PlayerSpd.y -= 0.4f;
		}
	}

	void setScale();//サイズ設定
	//プレイヤー
	cocos2d::Sprite* s_player;

	static const int PLAYER_MAX_SIZE = 64;

private:

};

