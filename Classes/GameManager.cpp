#include "GameManager.h"

USING_NS_CC;

//プレイシーン

const  int GameManager::BOX_COLLIDER = 10;			//あたり判定時に使用するタイルレイヤーの淵から少しだけ内側に入っているか確かめるための数


//////////////キャラクターレイヤー//////
//////////////キャラクター//////////////
Vec2 GameManager::PlayerSpd = (Vec2(6.0f,-4.0f));//速度
Vec2  GameManager::PlayerSize = Vec2(64, 64);//サイズ
Vec2  GameManager::PlayerPos = Vec2(50.0f,300.0f);//座標
float  GameManager::ScoreCorrection = 0.0f;//スコア補正
bool GameManager::JumpFlag = false;//地面についているか
bool GameManager::RightFlag = false;//右側に当たったか
int  GameManager::JumpCnt = 0;//ジャンプフラグ


int GameManager::FirstTouchCnt = 0;//最初のタッチからどれだけ経過したか
bool GameManager::FirstTouchFlag = false;//最初のタッチが呼ばれたか

///////////////ステージレイヤー/////////
TMXTiledMap*  GameManager::map = nullptr;//マップ
const Vec2 GameManager::MAP_SIZE = Vec2(960 * 2, 640);//マップ大きさ
const Vec2 GameManager::LAYRE_SIZE = Vec2(64,64);//レイヤーの大きさ
std::vector<Vec2> GameManager::FloorPos;//床座標


//斜面

std::vector<Vec2> GameManager::LeftPos;//左端
std::vector<Vec2> GameManager::RightPos;//右端

										//イテレータの値を格納する
cocos2d::Vec2 GameManager::SaveRight;
cocos2d::Vec2 GameManager::SaveLeft;

///////////////床/////////////////////
float GameManager::SlopePosY = 0.0f;//斜面座標Y
//////////////コイン//////////////

int  GameManager::CoinCnt = 0;//コインをカウント
std::vector<int>  GameManager::CoinPoint;//コインのポイント


/////////////////UIレイヤー/////////////////
/////////////////スコア////////////////
std::vector<cocos2d::Sprite*> GameManager::s_score;//コイン
int GameManager::ScoreMaxDigit = 0;//最大桁数
int GameManager::Score = 0;//スコア
int GameManager::SaveScore = 0;//スコアを保存する
/////////////////場所////////////////////////
int GameManager::DistanceMaxDigit = 0;//最大桁数
int GameManager::Digit = 0;//桁数
int GameManager::Distance = 0;//距離

int GameManager::SaveDistance = 0;//距離を保存する
int GameManager::SpriteCnt = 0;//何個目のスプライトかカウントする
bool GameManager::UsedFlag = false;//この関数がすでに呼ばれたか


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
				//GameManager::SlopePosY = v.y / v.x  * Object.x + Apos.y - GameManager::PlayerSize.y * 2;
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


