/***************************************************************************
*|
*|	概要　　リザルトレイヤー
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "CharacterLayer.h"

USING_NS_CC;

bool CharacterLayer::init()
{
	if (!Layer::init()) {

		return false;

	}

	//レイヤーにノードを集約
	character = Character::create();
	this->addChild(character);

	//毎フレーム呼び出す
	this->scheduleUpdate();

	return true;
}

/***************************************************************************
*|	概要　	毎フレーム呼び出す
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::update(float date)
{
	//移動する
	character->Move();
	//重力
	character->Gravity();

	//プレイヤーと斜面のあたり判定
	AfterHittingSlope();
}


/***************************************************************************
*|	概要　	プレイヤーと斜面のあたり判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::AfterHittingSlope()
{
	Vec2 a = Vec2(200, 200);
	Vec2 b = Vec2(600, 264);

	if(GameManager::DiagonalCollisionDetermination
	(a, b, GameManager::PlayerPos) == up)
	{
		GameManager::PlayerSpd.y = 0.0f;
		GameManager::PlayerPos.y = GameManager::SlopePosY/* - GameManager::PlayerSize.y / 2*/;
	}
}
