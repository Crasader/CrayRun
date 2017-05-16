#include "GameManager.h"

USING_NS_CC;
//プレイシーン

const  int GameManager::BOX_COLLIDER = 10;			//あたり判定時に使用するタイルレイヤーの淵から少しだけ内側に入っているか確かめるための数
const  int GameManager::BOX_COLLIDER2 = 40;			//あたり判定時に使用するタイルレイヤーの淵から少しだけ内側に入っているか確かめるための数

float GameManager::WorldPosX = 0.0f;

//////////////キャラクターレイヤー//////
//////////////キャラクター//////////////
Vec2 GameManager::PlayerSpd = (Vec2(6.0f,-4.0f));//速度
Vec2  GameManager::PlayerSize = Vec2(96, 96);//サイズ
Vec2  GameManager::PlayerPos = Vec2(300.0f,300.0f);//座標
float  GameManager::ScoreCorrection = 1.0f;//スコア補正
bool GameManager::RightFlag = false;//右側に当たったか

int GameManager::FirstTouchCnt = 0;//最初のタッチからどれだけ経過したか
bool GameManager::FirstTouchFlag = false;//最初のタッチが呼ばれたか
int GameManager::PlayerMapPos = 0;//何番目の座標にいるか


///////////////ステージレイヤー/////////
std::vector<cocos2d::TMXTiledMap*>  GameManager::map;//マップ

const Vec2 GameManager::MAP_SIZE = Vec2(960 * 2, 640);//マップ大きさ
const Vec2 GameManager::LAYRE_SIZE = Vec2(64,64);//レイヤーの大きさ
int  GameManager::MapLoopCnt = 0;//ステージをループさせた回数
std::vector<std::vector<Vec2>> GameManager::AllFloorPos;//床座標

//////////////斜面////////////////////
int  GameManager::SlopeCnt = 0;//斜面カウント
std::vector<std::vector<Vec2>> GameManager::AllLeftPos;
std::vector<std::vector<Vec2>> GameManager::AllRightPos;


///////////////床/////////////////////
float GameManager::SlopePosY = 0.0f;//斜面座標Y

/////////////粘土ステージ////////
std::vector<std::vector<cocos2d::Vec2>>  GameManager::AllCrayFloorPos;//粘土床座標
const Vec2   GameManager::MAX_CRAYSTAGESIZE = Vec2(192, 320);////粘土床の最大サイズ

std::vector<Vec2>   GameManager::CrayFloorSize;//粘土床の大きさ
int GameManager::CraySizeChangeCnt = 0;//どの粘土床のサイズを変更するか
bool GameManager::CraySizeChangeFlag = false;//粘土床のサイズ変更するか


//////////////コイン//////////////
std::vector<int>  GameManager::CoinPoint;//コインのポイント
std::vector<std::vector<Vec2>> AllLeftPos;//全ての斜面左端の座標
std::vector<std::vector<Vec2>> AllRightPos;//全ての斜面右端の座標

/////////////金型////////////////

int GameManager::Mold = 0;//金型
bool GameManager::ChangeMold = false;//金型変化あるか

int GameManager::MoldCnt = 0;

std::vector<cocos2d::Vec2> GameManager::MoldPos;//金型の座標

Vec2 GameManager::MoldSpd = Vec2(0, -4);
/////////////////UIレイヤー/////////////////
/////////////////スコア////////////////
int GameManager::Score = 0;//スコア
/////////////////場所////////////////////////
int GameManager::SaveDistance = 0;//距離を保存する


/////////////////カメラ//////////////////////.

float GameManager::m_cameraposx = 480.0f;
const float GameManager::m_cameraspdx = GameManager::PlayerSpd.x;




GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

/************************************************************************************
*|	概要　　衝突判定判定
*|	引数　　オブジェクト座標,オブジェクトサイズ,プレイヤー座標,オブジェクトサイズ
*|　戻り値　0:空中	1:マップレイヤーの上に乗った	2:マップレイヤーの右側に当たった
*************************************************************************************/
Direction  GameManager::CollisionDetermination(Vec2 Apos,Vec2 Asize, Vec2 Bpos,Vec2 Bsize)
{
	//マップレイヤーの上に乗ったか
	if (Apos.x <= Bpos.x + Bsize.x / 2)
	{
		if (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		{
			if (Apos.y >= Bpos.y)
			{
				if (Apos.y - GameManager::BOX_COLLIDER <= Bpos.y)
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
				if (Apos.y - Asize.y + GameManager::BOX_COLLIDER >= Bpos.y + Bsize.y)
				{
					{
						return under;
					}
				}
			}
		}
	}

	//マップレイヤーの左側に当たったか
	if (Apos.x + GameManager::BOX_COLLIDER >= Bpos.x + Bsize.x / 2)
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
	if (Apos.x + Asize.x - GameManager::BOX_COLLIDER <= Bpos.x - Bsize.x / 2)
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
Direction  GameManager::CollisionDetermination2(Vec2 Apos, Vec2 Asize, Vec2 Bpos, Vec2 Bsize)
{
	//マップレイヤーの上に乗ったか
	if (Apos.x <= Bpos.x + Bsize.x / 2)
	{
		if (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		{
			if (Apos.y >= Bpos.y)
			{
				if (Apos.y - GameManager::BOX_COLLIDER2 <= Bpos.y)
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
				if (Apos.y - Asize.y + GameManager::BOX_COLLIDER2 >= Bpos.y + Bsize.y)
				{
					{
						return under;
					}
				}
			}
		}
	}

	//マップレイヤーの左側に当たったか
	if (Apos.x + GameManager::BOX_COLLIDER2 >= Bpos.x + Bsize.x / 2)
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
	if (Apos.x + Asize.x - GameManager::BOX_COLLIDER2 <= Bpos.x - Bsize.x / 2)
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
Direction GameManager::DiagonalCollisionDetermination(Vec2 Apos, Vec2 Bpos, Vec2 Object) {

	Vec2 v;
	Vec2 A;
	Vec2 B;
	float w;
	float d;
	bool direction;

	//キャラクターの中心を求める
	Object.y += GameManager::PlayerSize.y;

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
				GameManager::SlopePosY = v.y / v.x  * (Object.x - Apos.x ) + Apos.y; /*- GameManager::PlayerSize.y */ 

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
bool GameManager::HitJudgment(Vec2 Apos, Vec2 Asize, Vec2 Bpos, Vec2 Bsize)
{

	if ((Apos.x <= Bpos.x + Bsize.x / 2)
		&& (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		&& (Apos.y >= Bpos.y)
		&& (Apos.y - Asize.y  /2  <= Bpos.y + Bsize.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}


