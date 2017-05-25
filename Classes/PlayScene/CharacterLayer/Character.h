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

	int walkCnt;//歩いたときのカウント

	void Move();//移動
	void Jump();//ジャンプする
	virtual void Animation();

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
			GameManager::PlayerSpd.y -= 0.6f;
		}

	}

	void setScale();//サイズ設定
	//プレイヤー
	cocos2d::Sprite* s_player;
	//プレイヤーの最大サイズ
	const int PLAYER_MAX_SIZE = 96;
	int i = 0;

	//何番目のマップにいるか求める
	void GetLoopPos()
	{
		GameManager::PlayerMapPos = GameManager::PlayerPos.x / GameManager::MAP_SIZE.x;
		//if (GameManager::PlayerMapPos == i)
		//{
		//	int a = 0;
		//	i++;
		//}
	/*if (static_cast<int>(GameManager::PlayerPos.x) % static_cast<int>(GameManager::MAP_SIZE.x) != 0)
		{
			GameManager::PlayerMapPos++;
		}*/
	}


	//キャラクタ上方向上限
	void JumpBan() {
		if (GameManager::PlayerPos.y > GameManager::SCREEN_SIZE.y - GameManager::PlayerSize.y + 5	)
		{
			GameManager::PlayerSpd.y = 0; 
			GameManager::PlayerPos.y = GameManager::SCREEN_SIZE.y - GameManager::PlayerSize.y ;
		}
	}

	float JumpSize;//ジャンプするおおきさ
	

	int JumpCnt;//ジャンプのカウント
	bool JumpFlag;//ジャンプできるか

	bool isScale;//座標の大きさが変更されているかtrue：されている,false：されていない


	bool FloormultipleFlag;//床の下に当たっているか
};

