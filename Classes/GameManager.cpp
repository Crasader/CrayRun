#include "GameManager.h"

USING_NS_CC;

const Vec2 GameManager::LAYRE_SIZE = Vec2(64, 64);//レイヤーの大きさ

//プレイシーン
float GameManager::WorldPosX = 0.0f;
bool GameManager::GameOverFlag = false;//ゲームオーバーフラグ
bool GameManager::InvincibleFlag;//無敵常態かどうか

const Vec2 GameManager::SCREEN_SIZE= Vec2(960,640);//画面サイズ
const Vec2 GameManager::TOUCH_SIZE = Vec2(32.0f,32.0f);	//タッチの大きさ

//////////////キャラクターレイヤー//////
//////////////キャラクター//////////////
Vec2 GameManager::PlayerSpd = (Vec2(6.0f,-4.0f));//速度
Vec2  GameManager::PlayerSize = Vec2(96, 96);//サイズ
Vec2  GameManager::PlayerPos = Vec2(300.0f, GameManager::LAYRE_SIZE.y * 4);//座標
int  GameManager::JumpCnt = 0;//ジャンプする回数
bool  GameManager::JumpFlag = false;//ジャンプできるか
bool  GameManager::JumpState = false;//ジャンプできるか


float  GameManager::ScoreCorrection = 1.0f;//スコア補正


//


bool GameManager::FirstTouchFlag = false;//最初のタッチが呼ばれたか
int GameManager::PlayerMapPos = 0;//何番目の座標にいるか


///////////////ステージレイヤー/////////
std::vector<cocos2d::TMXTiledMap*>  GameManager::map;//マップ

const Vec2 GameManager::MAP_SIZE = Vec2(300 * 64, 640);//マップ大きさ
int  GameManager::MapLoopCnt = 0;//ステージをループさせた回数
std::vector<std::vector<Vec2>> GameManager::AllFloorPos;//床座標


///////////////床/////////////////////
float GameManager::SlopePosY = 0.0f;//斜面座標Y

//////////////コイン//////////////
std::vector<std::vector<Vec2>> AllLeftPos;//全ての斜面左端の座標
std::vector<std::vector<Vec2>> AllRightPos;//全ての斜面右端の座標

/////////////金型////////////////

GameManager::CharacterKind GameManager::Mold = Normal;//金型
bool GameManager::ChangeMold = false;//金型変化あるか

int GameManager::MoldCnt = 0;
std::vector<cocos2d::Vec2> GameManager::MoldPos;//金型の座標
/////////////////UIレイヤー/////////////////
/////////////////スコア////////////////
int GameManager::Score = 0;//スコア
/////////////////場所////////////////////////
int GameManager::SaveDistance = 0;//距離を保存する
int GameManager::TotalDistance = 0;//最終スコア

/////////////////カメラ//////////////////////.

float GameManager::m_cameraposx = 480.0f;
const float GameManager::m_cameraspdx = GameManager::PlayerSpd.x;


//初期化関数
void GameManager::Initialize()
{
	WorldPosX = 0.0f;
	GameOverFlag = false;//ゲームオーバーフラグ
	InvincibleFlag = false;//無敵常態かどうか

	JumpCnt = 0;//ジャンプする回数
	JumpFlag = false;//ジャンプできるか
	map.clear();//マップ
	AllFloorPos.clear();//床座標
	//AllLeftPos.clear();
	//AllRightPos.clear();
	//AllLeftPos.clear();//全ての斜面左端の座標
	//AllRightPos.clear();//全ての斜面右端の座標
	MoldPos.clear();//金型の座標



	//////////////キャラクターレイヤー//////
	//////////////キャラクター//////////////
	PlayerSpd = Vec2(6.0f, -4.0f);//速度
	PlayerSize = Vec2(96, 96);//サイズ
	ScoreCorrection = 1.0f;//スコア補正
	PlayerPos = (Vec2(300.0f, GameManager::LAYRE_SIZE.y * 4));//座標
	


	FirstTouchFlag = false;//最初のタッチが呼ばれたか
	PlayerMapPos = 0;//何番目の座標にいるか


	///////////////ステージレイヤー/////////

	MapLoopCnt = 0;//ステージをループさせた回数


	
	
	///////////////床/////////////////////
	SlopePosY = 0.0f;//斜面座標Y

	/////////////金型////////////////

	Mold = Normal;//金型
	ChangeMold = false;//金型変化あるか


	AllLeftPos.crend();//全ての斜面左端の座標
	AllRightPos.crend();//全ての斜面右端の座標



	/////////////////UIレイヤー/////////////////
	/////////////////スコア////////////////
	Score = 0;//スコア
	/////////////////場所////////////////////////
	SaveDistance = 0;//距離を保存する


	/////////////////カメラ//////////////////////.

	m_cameraposx = 480.0f;
}

/************************************************************************************
*|	概要　　衝突判定判定
*|	引数　　オブジェクト座標,オブジェクトサイズ,プレイヤー座標,オブジェクトサイズ
*|　戻り値　0:空中	1:マップレイヤーの上に乗った	2:マップレイヤーの右側に当たった
*************************************************************************************/
GameManager::Direction  GameManager::CollisionDetermination(Vec2 Apos,Vec2 Asize, Vec2 Bpos,Vec2 Bsize)
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
GameManager::Direction  GameManager::CollisionDetermination2(Vec2 Apos, Vec2 Asize, Vec2 Bpos, Vec2 Bsize)
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

	//GameManager::SlopePosY = LineVec.y / LineVec.x  * (CirclePos.x - Apos.x) + Apos.y;


	//何にも当たっていない
	return exception;
}



/************************************************************************************
*|	概要　　衝突判定(斜辺)
*|	引数　　線左端座標,線右端座標,円中心座標
*|　戻り値　true当たった　false 当たってない
*************************************************************************************/
GameManager::Direction GameManager::DiagonalCollisionDetermination(Vec2 Apos, Vec2 Bpos, Vec2 CirclePos) {

	//線のベクトル
	Vec2 LineVec;
	//円と線の頂点Aのベクトル
	Vec2 Avec;
	//円と線の頂点Bのベクトル
	Vec2 Bvec;
	//線の頂点AとBの距離
	float LineDistance;
	//線と円の中心距離
	float Line2CircleDistance;
	//円が上下どちらから当たったか
	bool direction;

	//線のベクトルを求める
	LineVec = Bpos - Apos;
	//円と線の頂点ABのベクトルをそれぞれ求める
	Avec = CirclePos - Apos;
	Bvec = CirclePos - Bpos;


	//AposとBposの距離を求める
	LineDistance = Apos.distance(Bpos);

	//外積を使い線と円の中心距離を求める
	Line2CircleDistance = LineVec.cross(Avec) / LineDistance;

	//当たったとしたら円が上から当たった
	if (Line2CircleDistance < 0)
	{
		//正の数に変える
		Line2CircleDistance *= -1.0f;
	
		direction = false;
	}
	//当たったとしたら円が下から当たった
	else
	{
		direction = true;
	}

	//	当たっているか
	if (Line2CircleDistance <= PlayerSize.y)
	{
		//延長線上の判定を除外する
		//両頂点から円に伸びる線の角が鈍角である場合は衝突しない
		if (Avec.dot(LineVec) * Bvec.dot(LineVec) <= 0)
		{
			//プレイヤーが上から当たった場合
			if (direction == true)
			{

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



/************************************************************************************
*|	概要　　あたり判定
*|	引数　　対象二つの座標
*|　戻り値　true当たった　false 当たってない
*************************************************************************************/
bool GameManager::HitJudgment2(Vec2 Apos, Vec2 Asize, Vec2 Bpos, Vec2 Bsize)
{

	if ((Apos.x <= Bpos.x + Bsize.x)
		&& (Apos.x + Asize.x >= Bpos.x - Bsize.x )
		&& (Apos.y >= Bpos.y)
		&& (Apos.y - Asize.y  <= Bpos.y + Bsize.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

