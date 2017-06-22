/***************************************************************************
*|
*|	概要　斜面スプライトクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/6/5
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "SlopeSprite.h"
/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace std;
/***************************************************************************
*|	概要　　初期化処理
*|	引数　　画像名,左右頂点座標
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool SlopeSprite::init(std::string filename, Vec2 Leftpos, Vec2 RightPos)
{
	if (!SlopeSprite::initWithFile(filename)) {

		return false;
	}
	//左右頂点座標の初期化
	m_left_pos = Leftpos;
	m_right_pos = RightPos;
	//毎フレーム呼ぶ
	this->scheduleUpdate();

	return true;
}


/***************************************************************************
*|	概要　　スプライトを作成する。
*|	引数　	画像名、左右頂点座標
*|　戻り値　シーンのアドレス
****************************************************************************/
SlopeSprite* SlopeSprite::create(string filename, Vec2 Leftpos, Vec2 RightPos)
{
	//メモリ確保
	SlopeSprite *pRet = new(nothrow)SlopeSprite();

	if (pRet && pRet->init(filename, Leftpos, RightPos))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}

}







/***************************************************************************
*|	概要　  斜面とプレイヤの当たり判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void SlopeSprite::CollisionPlayer()
{

		//衝突判定（斜面）
		GameManager::Direction HitFlag = 
		GameManager::DiagonalCollisionDetermination(m_left_pos, m_right_pos, GameManager::PlayerPos);
		//上に乗った時
		if (HitFlag == GameManager::up)
		{
			if (!GameManager::JumpState)
			{
				GameManager::PlayerSpd.y = 0.0f;
				//埋まった分を押し出す
				GameManager::PlayerPos.y = GameManager::SlopePosY;				//ジャンプ可能にする
				GameManager::JumpCnt = 0;
				GameManager::JumpFlag = true;
;
			}


		}

			
}



void SlopeSprite::update(float data)
{

	//プレイヤーとの衝突判定
	CollisionPlayer();


}

