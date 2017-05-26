/***************************************************************************
*|
*|	概要　キャラクタクラスの定義
*|　作成者　GS2 16 中田湧介,GS2 24 山本悠雅
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "Character.h"

#include "audio/include//AudioEngine.h"



/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace experimental;


bool Character::init()
{
	if (!Node::init()) {

		return false;
	}



	if (s_player == nullptr){
		//プレイヤー作成
		s_player = Sprite::create("Images/Player2.png");
		s_player->setPosition(GameManager::PlayerPos);
		s_player->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(s_player);
	}
	else {
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

	JumpSize = 11.0f;
	FloormultipleFlag = false;
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
	JumpCnt++;

	//ジャンプ可能ならジャンプさせる
	if (JumpFlag == true)
	{
		//ジャンプ音再生
		AudioEngine::play2d("Sounds/jump04.mp3");
		GameManager::PlayerSpd.y = JumpSize;
	}
	//二回ジャンプしたらジャンプ不可にする
	if (JumpCnt == 2)
	{
		JumpCnt = 0;
		JumpFlag = false;
	}
}

void Character::Animation()
{
	Texture2D* texture;
	
	//ジャンプできるときかつジャンプをまだしていないとき（歩いてるとき）
	if (JumpCnt == 0 && JumpFlag == true)
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

		if (GameManager::PlayerSize.x == PLAYER_MAX_SIZE && GameManager::PlayerSize.y == PLAYER_MAX_SIZE)
		{
			isScale = false;
		}

		//サイズを適用する
		s_player->setScale(GameManager::PlayerSize.x / PLAYER_MAX_SIZE, GameManager::PlayerSize.y / PLAYER_MAX_SIZE);
	}
}