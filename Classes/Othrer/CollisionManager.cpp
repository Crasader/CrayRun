#include "CollisionManager.h"

USING_NS_CC;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}



/************************************************************************************
*|	概要　　衝突判定判定
*|	引数　　オブジェクト座標,オブジェクトサイズ,プレイヤー座標,オブジェクトサイズ
*|　戻り値　0:空中	1:マップレイヤーの上に乗った	2:マップレイヤーの右側に当たった
*************************************************************************************/
CollisionManager::Direction  CollisionManager::CollisionDetermination(Vec2 Apos, Vec2 Asize, Vec2 Bpos, Vec2 Bsize)
{
	//マップレイヤーの上に乗ったか
	if (Apos.x <= Bpos.x + Bsize.x / 2)
	{
		if (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		{
			if (Apos.y >= Bpos.y)
			{
				if (Apos.y - CollisionManager::BOX_COLLIDER <= Bpos.y)
				{
					{
						return up;
					}
				}
			}
		}
	}



	//マップレイヤーの下に乗ったか
	if (Apos.x <= Bpos.x + Bsize.x / 2)
	{
		if (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		{
			if (Apos.y - Asize.y <= Bpos.y + Bsize.y)
			{
				if (Apos.y - Asize.y + CollisionManager::BOX_COLLIDER >= Bpos.y + Bsize.y)
				{
					{
						return under;
					}
				}
			}
		}
	}

	//マップレイヤーの左側に当たったか
	if (Apos.x + CollisionManager::BOX_COLLIDER >= Bpos.x + Bsize.x / 2)
	{
		if (Apos.x <= Bpos.x + Bsize.x / 2)
		{
			if (Apos.y >= Bpos.y)
			{
				if (Apos.y - Asize.y <= Bpos.y + Bsize.y)
				{
					{
						return left;
					}
				}
			}
		}
	}


	//マップレイヤーの右側に当たったか
	if (Apos.x + Asize.x - CollisionManager::BOX_COLLIDER <= Bpos.x - Bsize.x / 2)
	{
		if (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		{
			if (Apos.y >= Bpos.y)
			{
				if (Apos.y - Asize.y <= Bpos.y + Bsize.y)
				{
					{
						return right;
					}
				}
			}
		}
	}



	//何にも当たっていない
	return exception;
}

/************************************************************************************
*|	概要　　衝突判定判定
*|	引数　　オブジェクト座標,オブジェクトサイズ,プレイヤー座標,オブジェクトサイズ
*|　戻り値　0:空中	1:マップレイヤーの上に乗った	2:マップレイヤーの右側に当たった
*************************************************************************************/
CollisionManager::Direction  CollisionManager::CollisionDetermination2(Vec2 Apos, Vec2 Asize, Vec2 Bpos, Vec2 Bsize)
{
	//マップレイヤーの上に乗ったか
	if (Apos.x <= Bpos.x + Bsize.x / 2)
	{
		if (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		{
			if (Apos.y >= Bpos.y)
			{
				if (Apos.y - BOX_COLLIDER2 <= Bpos.y)
				{
					{
						return up;
					}
				}
			}
		}
	}



	//マップレイヤーの下に乗ったか
	if (Apos.x <= Bpos.x + Bsize.x / 2)
	{
		if (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		{
			if (Apos.y - Asize.y <= Bpos.y + Bsize.y)
			{
				if (Apos.y - Asize.y + BOX_COLLIDER2 >= Bpos.y + Bsize.y)
				{
					{
						return under;
					}
				}
			}
		}
	}

	//マップレイヤーの左側に当たったか
	if (Apos.x + BOX_COLLIDER2 >= Bpos.x + Bsize.x / 2)
	{
		if (Apos.x <= Bpos.x + Bsize.x / 2)
		{
			if (Apos.y >= Bpos.y)
			{
				if (Apos.y - Asize.y <= Bpos.y + Bsize.y)
				{
					{
						return left;
					}
				}
			}
		}
	}


	//マップレイヤーの右側に当たったか
	if (Apos.x + Asize.x - BOX_COLLIDER2 <= Bpos.x - Bsize.x / 2)
	{
		if (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		{
			if (Apos.y >= Bpos.y)
			{
				if (Apos.y - Asize.y <= Bpos.y + Bsize.y)
				{
					{
						return right;
					}
				}
			}
		}
	}



	//何にも当たっていない
	return exception;
}



/************************************************************************************
*|	概要　　衝突判定(斜辺)
*|	引数　　斜辺左端座標,斜辺右端座標,オブジェクト座標
*|　戻り値　true当たった　false 当たってない
*************************************************************************************/
CollisionManager::Direction CollisionManager::DiagonalCollisionDetermination(Vec2 Apos, Vec2 Bpos, Vec2 Object) {

	Vec2 v;
	Vec2 A;
	Vec2 B;
	float w;
	float d;
	bool direction;

	//キャラクターの中心を求める
	Object.y += CollisionManager::PlayerSize.y;

	v = Bpos - Apos;
	A = Object - Apos;
	B = Object - Bpos;

	//v.normalize();

	float f = v.y;

	//AposとBposの距離
	w = Apos.distance(Bpos);
	//
	d = v.cross(A) / w;

	//マイナスの時
	if (d < 0)
	{
		//整数に変える
		d *= -1.0f;
		direction = false;
	}
	else
	{
		direction = true;
	}

	//	当たっているか
	if (d <= PlayerSize.y)
	{
		//延長線上の判定を除外する
		if (A.dot(v) * B.dot(v) <= 0)
		{
			//プレイヤーが上から当たった場合
			if (direction == true)
			{
				CollisionManager::SlopePosY = v.y / v.x  * (Object.x - Apos.x) + Apos.y; /*- GameManager::PlayerSize.y */

				return up;
			}
			//プレイヤーが下から当たった場合
			else
			{
				return under;
			}
		}
	}

	//何にも当たっていない
	return exception;

}

/************************************************************************************
*|	概要　　あたり判定
*|	引数　　対象二つの座標
*|　戻り値　true当たった　false 当たってない
*************************************************************************************/
bool CollisionManager::HitJudgment(Vec2 Apos, Vec2 Asize, Vec2 Bpos, Vec2 Bsize)
{

	if ((Apos.x <= Bpos.x + Bsize.x / 2)
		&& (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		&& (Apos.y >= Bpos.y)
		&& (Apos.y - Asize.y / 2 <= Bpos.y + Bsize.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}



/************************************************************************************
*|	概要　　あたり判定
*|	引数　　対象二つの座標
*|　戻り値　true当たった　false 当たってない
*************************************************************************************/
bool CollisionManager::HitJudgment2(Vec2 Apos, Vec2 Asize, Vec2 Bpos, Vec2 Bsize)
{

	if ((Apos.x <= Bpos.x + Bsize.x)
		&& (Apos.x + Asize.x >= Bpos.x - Bsize.x)
		&& (Apos.y >= Bpos.y)
		&& (Apos.y - Asize.y <= Bpos.y + Bsize.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

