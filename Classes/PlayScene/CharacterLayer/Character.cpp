/***************************************************************************
*|
*|	概要　スコアクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "Character.h"


USING_NS_CC;
using namespace cocos2d::experimental;



bool Character::init()
{
	if (!Node::init()) {

		return false;
	}

	//プレイヤー作成
	s_player = Sprite::create("Images/1.png");
	s_player->setPosition(GameManager::PlayerPos);
	s_player->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(s_player);





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
	JumpBy* jumpaction = JumpBy::create(0.5f, Vec2(0,0), 64.0f, 1);
	this->runAction(jumpaction);

}


/***************************************************************************
*|	概要　　重力
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void Character::Gravity()
{
	if (GameManager::SlopeFalg == true)
	{
		GameManager::PlayerSpd.y = 0.0f;
	}
	else
	{
		GameManager::PlayerSpd.y = -4.0f;
	}
}


