/***************************************************************************
*|
*|	概要　キャラクタクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "Character.h"

#include "audio/include/AudioEngine.h"



/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace experimental;


/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool Character::init()
{
	if (!Node::init()) {

		return false;
	}



	if (s_player == nullptr){
		//プレイヤー作成
		s_player = Sprite::create("Images/Player2.png");
		s_player->setPosition(GameManager::PlayerPos);
		s_player->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		this->addChild(s_player);


		//// 作成したパーティクルのプロパティリストを読み込み
		//particle = ParticleSystemQuad::create("Particle/rDust.plist");
		////パーティクルのメモリーリーク回避（★重要）
		//particle->setAutoRemoveOnFinish(true);
		//// パーティクルを開始
		//particle->resetSystem();
		//// パーティクルを配置
		//this->addChild(particle);
	}
	else 
	{
		Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/Player2.png");
	}

	//プレイヤが最大の大きさじゃないときtrueに、最大の大きさならfalse
	if (GameManager::PlayerSize.x < PLAYER_MAX_SIZE && GameManager::PlayerSize.y < PLAYER_MAX_SIZE)
	{
		isScale = true;
	}
	else 
	{
		isScale = false;
	}
		
	walkCnt = 0;
	JumpSize = 
	JumpSize = 11.0f;
	FloormultipleFlag = false;
	GameManager::ScoreCorrection = SCORECORRECTION;
	return true;
}

/***************************************************************************
*|	概要　　移動する
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void Character::Move()
{
	//座標に速度をたす
	GameManager::PlayerPos += GameManager::PlayerSpd;
	//座標を適用させる
	s_player->setPosition(GameManager::PlayerPos);

	////土埃の座標
	//if (GroundFlag == true)
	//{
	//	//表示する
	//	particle->setVisible(true);
	//	// パーティクルを表示する場所の設定
	//	particle->setPosition(GameManager::PlayerPos - Vec2(GameManager::PlayerSize.x / 2 , 0.0f));
	//}
	//else
	//{
	//	//非表示にする
	////	particle->setVisible(false);
	//}
	
	walkCnt++;
	Animation();
}

/***************************************************************************
*|	概要　  ジャンプ
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void Character::Jump()
{
	//ジャンプした回数をインクリメント
	GameManager::JumpCnt++;

	//ジャンプ可能ならジャンプさせる
	if (GameManager::JumpFlag == true)
	{
		//ジャンプ音再生
		AudioEngine::play2d("Sounds/jump04.ogg");
		GameManager::PlayerSpd.y = JumpSize;
	}
	//二回ジャンプしたらジャンプ不可にする
	if (GameManager::JumpCnt == 2)
	{
		GameManager::JumpCnt = 0;
		GameManager::JumpFlag = false;
	}
}

void Character::Animation()
{
	Texture2D* texture;
	
	//ジャンプできるときかつジャンプをまだしていないとき（歩いてるとき）
	if (GameManager::JumpCnt == 0 && GameManager::JumpFlag == true)
	{
		switch (walkCnt / AnimationSpd % 4)
		{
		case 0:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Player2.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());

			break;
		case 1:
		case 3:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Player_w.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());

			break;
		case 2:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Player_w2.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());

			break;
		}
	}
	else
	{
		texture = TextureCache::sharedTextureCache()->addImage("Images/Player_j.png");

		s_player->setTexture(texture);
		s_player->setContentSize(texture->getContentSize());
	}


}

/***************************************************************************
*|	概要　  スケールの設定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void Character::setScale()
{

	if (FloormultipleFlag == false)
	{
		//プレイヤーのサイズXが通常より小さいとき
		if (GameManager::PlayerSize.x < PLAYER_MAX_SIZE)
		{
			//少しずつ大きくする
			GameManager::PlayerSize.x += 0.15f;
		}
		else if (GameManager::PlayerSize.x > PLAYER_MAX_SIZE)
		{
			GameManager::PlayerSize.x = PLAYER_MAX_SIZE;

		}

		//プレイヤーのサイズYが通常より小さいとき
		if (GameManager::PlayerSize.y < PLAYER_MAX_SIZE)
		{
			GameManager::PlayerSize.y += 0.35f;
		}
		else if (GameManager::PlayerSize.y > PLAYER_MAX_SIZE)
		{
			GameManager::PlayerSize.y = PLAYER_MAX_SIZE;
		}

		if (GameManager::PlayerSize.x == PLAYER_MAX_SIZE && GameManager::PlayerSize.y == PLAYER_MAX_SIZE || GameManager::Mold == GameManager::Slime)
		{
			isScale = false;
		}

		//サイズを適用する
		s_player->setScale(GameManager::PlayerSize.x / PLAYER_MAX_SIZE, GameManager::PlayerSize.y / PLAYER_MAX_SIZE);
	}
}