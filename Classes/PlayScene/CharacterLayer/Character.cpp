/***************************************************************************
*|
*|	概要　キャラクタクラスの定義
*|　作成者　GS2 16 中田湧介,GS2 24 山本悠雅
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "Character.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;



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

		bool JumpFlag = true;//地面についているか
		int  JumpCnt = 0;//ジャンプフラグ


	}
	else {
		Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/Player2.png");

		bool JumpFlag = false;//地面についているか
		int  JumpCnt = 0;//ジャンプフラグ

	}

	JumpSize = 9.0f;
	ChangeScaleFlag = true;
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
		GameManager::PlayerSpd.y = JumpSize;
	}
	//二回ジャンプしたらジャンプ不能にする
	if (JumpCnt == 2)
	{
		JumpCnt = 0;
		JumpFlag = false;
	}
}

/***************************************************************************
*|	概要　  スケールの設定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void Character::setScale()
{
	//プレイヤーのサイズXが通常より小さいとき
	if (GameManager::PlayerSize.x < PLAYER_MAX_SIZE)
	{
		//少しずつ大きくする
		GameManager::PlayerSize.x += 0.1f;
	}
	else if (GameManager::PlayerSize.x > PLAYER_MAX_SIZE)
	{
		GameManager::PlayerSize.x = 96;
	}

	//プレイヤーのサイズYが通常より小さいとき
	if (GameManager::PlayerSize.y < PLAYER_MAX_SIZE)
	{
		GameManager::PlayerSize.y += 0.1f;
	}
	else if (GameManager::PlayerSize.y > PLAYER_MAX_SIZE)
	{
		GameManager::PlayerSize.y = 96;
	}

	//サイズを適用する
	s_player->setScale(GameManager::PlayerSize.x / PLAYER_MAX_SIZE, GameManager::PlayerSize.y / PLAYER_MAX_SIZE);

	if (GameManager::PlayerSize.x == PLAYER_MAX_SIZE && GameManager::PlayerSize.y == PLAYER_MAX_SIZE)
	{
		ChangeScaleFlag = true;
	}
}
