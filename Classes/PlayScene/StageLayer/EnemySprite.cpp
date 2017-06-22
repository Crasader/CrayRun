/***************************************************************************
*|
*|	概要　敵スプライトクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "NeedleSprite.h"
#include "EnemySprite.h"
#include "audio/include/AudioEngine.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace std;
using namespace experimental;
/***************************************************************************
*|	概要　　初期化処理
*|	引数　　画像名
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool EnemySprite::init(std::string filename)
{
	if (!Sprite::initWithFile(filename)) {

		return false;
	}
	//毎フレーム呼ぶ
	this->scheduleUpdate();

	//初期化
	m_animation_cnt = 0;
	return true;
}


/***************************************************************************
*|	概要　　スプライトを作成する。
*|	引数　	画像名
*|　戻り値　シーンのアドレス
****************************************************************************/
EnemySprite* EnemySprite::create(string filename)
{
	//メモリ確保
	EnemySprite *pRet = new(nothrow)EnemySprite();

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
*|	概要　　毎フレーム呼ばれる
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void EnemySprite::update(float delta)
{
	//アニメーション
	Animation();
	//プレイヤに当たっているか
	CollisionPlayer();
}


/***************************************************************************
*|	概要　  敵とプレイヤの当たり判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void EnemySprite::CollisionPlayer()
{
		switch (GameManager::CollisionDetermination
		(this->getPosition(), GameManager::LAYRE_SIZE,
			GameManager::PlayerPos, GameManager::PlayerSize))
		{
		case GameManager::right:
			//if (GameManager::Mold != GameManager::Phoenix) {
			//	GameManager::PlayerPos.x = getPosition() .x + GameManager::LAYRE_SIZE.x + GameManager::PlayerSize.x / 2 + 1;
			//	GameManager::PlayerSpd.x = 0.0f;
			//	GameManager::InvincibleFlag = true;
			//}
			break;
		case GameManager::left:
			//フェニックスでないかつ無敵常態でないか
			if (GameManager::Mold != GameManager::Phoenix ) {
				/*GameManager::PlayerPos.x = GameManager::AllFloorPosx[i] - GameManager::PlayerSize.x / 2;*/
				//GameManager::RightFlag = true;
				//GameManager::PlayerSpd.x = -6.0f;
				if (GameManager::InvincibleFlag == false)
				{
					//ドーロ君の以外か
					if (GameManager::Mold != GameManager::Normal)
					{
						//ギミックに当たったとしてゲームオーバー
						GameManager::InvincibleFlag = true;
					}
					else
					{
						//ゲームオーバー
						GameManager::GameOverFlag = true;
					}
				}
				
			}
			
	
		


			break;
		case GameManager::up:
			GameManager::PlayerPos.y = getPosition().y;
			
			//ジャンプ可能にする
			GameManager::JumpCnt = 0;
			GameManager::JumpFlag = true;

			
			//ジャンプ可能ならジャンプさせる
			if (GameManager::JumpFlag == true)
			{
				//ジャンプ音再生
				AudioEngine::play2d("Sounds/jump04.ogg");
				GameManager::PlayerSpd.y = 10;
			}

			////二回ジャンプしたらジャンプ不可にする
			//if (GameManager::JumpCnt == 2)
			///*if (GameManager::Mold != GameManager::Phoenix) */{
			//	GameManager::PlayerPos.y = this->getPosition().y - GameManager::LAYRE_SIZE.y - GameManager::PlayerSize.y;
			//	GameManager::PlayerSpd.y = 0.0f;
			//}
			break;
		default:
			break;
	}
}



/***************************************************************************
*|	概要　　アニメーション
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void EnemySprite::Animation()
{
	if (m_animation_cnt % 7 == 0)
	{
		Texture2D* texture;
		switch (m_animation_cnt / 7 % 6)
		{
		case 0:
		case 5:
			texture = TextureCache::sharedTextureCache()->addImage("Images/enemy1.png");
			this->setTexture(texture);
			break;
		case 1:
		case 4:
			texture = TextureCache::sharedTextureCache()->addImage("Images/enemy3.png");
			this->setTexture(texture);
			break;
		case 2:
		case 3:
			texture = TextureCache::sharedTextureCache()->addImage("Images/enemy2.png");

			this->setTexture(texture);
			break;
		default:
			break;
		}
	}
	m_animation_cnt++;
}

