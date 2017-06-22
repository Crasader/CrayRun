#pragma once
#include "CollisionManager.h"
#include "cocos2d.h"


class CollisionManager
{
public:
	//方向
	enum Direction
	{
		up,
		under,
		left,
		right,
		exception
	};



	CollisionManager();
	~CollisionManager();
	////////////////プレイシーン/////////////
	//衝突判定(ブロック)
	Direction  CollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	//衝突判定2(ブロック)
	Direction  CollisionDetermination2(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);

	//衝突判定(斜面)
	Direction DiagonalCollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Bpos, cocos2d::Vec2 Object);
	//当たり判定
	bool HitJudgment(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	bool HitJudgment2(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);

	//シーン変更時の初期化
	static void Initialize();

	//ゲームマネージャを生成する
	static CollisionManager* GetInstance() {
		//ゲームマネージャが存在していないか
		if (gamemanager == nullptr)
		{
			return gamemanager = new CollisionManager();
		}
	}


private:
	
	//ゲームマネージャのアドレスを格納する変数
	static CollisionManager* gamemanager;



private:
	const int BOX_COLLIDER = 10;			//あたり判定時に使用するタイルレイヤーの淵から少しだけ内側に入っているか確かめるための数
	const int BOX_COLLIDER2 = 40;			//あたり判定時に使用するタイルレイヤーの淵から少しだけ内側に入っているか確かめるための数


};

