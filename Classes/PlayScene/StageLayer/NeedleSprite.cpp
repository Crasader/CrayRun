/***************************************************************************
*|
*|	概要　コインクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "NeedleSprite.h"
/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace std;
/***************************************************************************
*|	概要　　初期化処理
*|	引数　　画像名
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool NeedleSprite::init(std::string filename)
{
	if (!Sprite::initWithFile(filename)) {

		return false;
	}
	
	m_state = true;

	//毎フレーム呼ぶ
	this->scheduleUpdate();

	return true;
}


/***************************************************************************
*|	概要　　スプライトを作成する。
*|	引数　	画像名
*|　戻り値　シーンのアドレス
****************************************************************************/
NeedleSprite* NeedleSprite::create(string filename)
{
	//メモリ確保
	NeedleSprite *pRet = new(nothrow)NeedleSprite();

	if (pRet && pRet->init(filename))
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
*|	概要　　マルチタッチ判定。
*|	引数　	タッチ座標
*|　戻り値　無し
****************************************************************************/

void NeedleSprite::MultiTouchColliosion(cocos2d::Vec2 touchpos)
{
	//有効なタッチの数
	const int EFFECTIVENESSTOUCH = 2;

	////タッチが当たった方向
	GameManager::Direction m_touch_collision_direction[EFFECTIVENESSTOUCH];
	//タッチがキャラクターに当たったか
	bool m_touch_collision[2];




	//タッチがプレイヤーに当たったか
	m_touch_collision[0] = GameManager::HitJudgment(
		touchpos - Vec2(GameManager::TOUCH_SIZE.x / 2, -GameManager::TOUCH_SIZE.y / 2), GameManager::TOUCH_SIZE,
		getPosition() + Vec2(MAX_SIZE.x / 2, -MAX_SIZE.y / 2), MAX_SIZE);
	//タッチ2がプレイヤーに当たったか
	m_touch_collision[1] = GameManager::HitJudgment(
		*(&touchpos + 1) - Vec2(GameManager::TOUCH_SIZE.x / 2, -GameManager::TOUCH_SIZE.y / 2), GameManager::TOUCH_SIZE,
		getPosition() + Vec2(MAX_SIZE.x / 2, -MAX_SIZE.y / 2), MAX_SIZE);

	//タッチが二つともプレイヤーに当たったか
	if (m_touch_collision[0] == true && m_touch_collision[1] == true)
	{
		// 普通の画像から変更
		Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/needle2.png");
		setTexture(texture);
		m_state = false;
	}
}

/***************************************************************************
*|	概要　  針とプレイヤの当たり判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void NeedleSprite::CollisionPlayer()
{

		//針がとがっているか
		if (m_state == true)
		{
			if (GameManager::HitJudgment(this->getPosition() + Vec2(-GameManager::LAYRE_SIZE.x / 2, GameManager::LAYRE_SIZE.y / 2),
				GameManager::LAYRE_SIZE, GameManager::PlayerPos, GameManager::PlayerSize) == true)
			{
				if (GameManager::Mold != GameManager::Normal)
				{
					GameManager::InvincibleFlag = true;
				}
				else
				{
					//無敵常態でないか
					if (GameManager::InvincibleFlag != true)
					{
						//	ゲームオーバーにする
						GameManager::GameOverFlag = true;
					}
				}
			
				
			}
		}
}



void NeedleSprite::update(float data)
{
	
	//プレイヤーとの衝突判定
	CollisionPlayer();
	
}

