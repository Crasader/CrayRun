/***************************************************************************
*|
*|	概要　　キャラクタクラスの宣言
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
	void Jump();//ジャンプする
	//重力
	void Gravity()
	{
		if (GameManager::RightFlag == false)
		{
			GameManager::PlayerSpd.x = 6.0f;
		}
		//重力加速度に上限を設ける
		if (GameManager::PlayerSpd.y >= -7.0f)
		{
			GameManager::PlayerSpd.y -= 0.4f;
		}
		//ジャンプがないときは関係なく加速度をつける
		else if (JumpFlag == false)
		{
			//GameManager::PlayerSpd.y -= 0.4f;
		}
	}

	void setScale();//サイズ設定
	//プレイヤー
	cocos2d::Sprite* s_player;
	//プレイヤーの最大サイズ
	const int PLAYER_MAX_SIZE = 96;


	//何番目のマップにいるか求める
	void GetLoopPos()
	{
		GameManager::PlayerMapPos = GameManager::PlayerPos.x / GameManager::MAP_SIZE.x;
	/*if (static_cast<int>(GameManager::PlayerPos.x) % static_cast<int>(GameManager::MAP_SIZE.x) != 0)
		{
			GameManager::PlayerMapPos++;
		}*/
	}

	//キャラクタ上方向上限
	void JumpBan() { if (GameManager::PlayerPos.y < 640)GameManager::PlayerSpd.y = 0; }

	float JumpSize;//ジャンプするおおきさ
	

	int JumpCnt;//ジャンプのカウント
	bool JumpFlag;//ジャンプできるか

	bool isScaleX;//X座標の大きさが変更されているかtrue：されている,false：されていない
	bool isScaleY;//Y座標の大きさが変更されているかtrue：されている,false：されていない
};

