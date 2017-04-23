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

	// Register Touch Event
	EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(CharacterLayer::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(CharacterLayer::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(CharacterLayer::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(CharacterLayer::onTouchesCancelled, this);

	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//_touchListener = listener;

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
	//プレイヤーと床の衝突判定
	AfterHittingFloor();
	//プレイヤーと斜面のあたり判定
	AfterHittingSlope();
}


/***************************************************************************
*|	概要　	タッチ時に呼び出される
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesBegan");
	character->Jump();

}

/***************************************************************************
*|	概要　	スワイプ時に呼び出される
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesMoved");
}

/***************************************************************************
*|	概要　	離したとき
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesEnded");
}

/***************************************************************************
*|	概要　	キャンセルされたとき
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesCancelled");
}



/***************************************************************************
*|	概要　	プレイヤーと床の衝突判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::AfterHittingFloor()
{
	//床の数だけループ
	for (int i = 0; i < GameManager::FloorCnt; i++)
	{
		switch (GameManager::CollisionDetermination
		(Vec2(GameManager::FloorPosx[i], GameManager::FloorPosy[i]), GameManager::LAYRE_SIZE,
			GameManager::PlayerPos, GameManager::PlayerSize))
		{
		case right:
			GameManager::PlayerPos.x = GameManager::FloorPosx[i] + GameManager::LAYRE_SIZE.x + GameManager::PlayerSize.x / 2 + 1;
			GameManager::PlayerSpd.x = 0.0f;
			break;
		case left:
			GameManager::PlayerPos.x = GameManager::FloorPosx[i] - GameManager::PlayerSize.x / 2;
			GameManager::PlayerSpd.x = 0.0f;
			break;
		case up:
			GameManager::PlayerPos.y = GameManager::FloorPosy[i];
			GameManager::PlayerSpd.y = 0.0f;
			//GameManager::JumpFlag = true;
			break;
		case under:
			GameManager::PlayerPos.y = GameManager::FloorPosy[i] - GameManager::LAYRE_SIZE.y - GameManager::PlayerSize.y - 1;
			GameManager::PlayerSpd.y = 0.0f;
			break;
		case exception:
			break;

		}
	}
	
}

/***************************************************************************
*|	概要　	プレイヤーと斜面の衝突判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::AfterHittingSlope()
{
	Vec2 a = Vec2(300, 400);
	Vec2 b = Vec2(700, 464);

	//衝突判定（斜面）
	Direction HitFlag = GameManager::DiagonalCollisionDetermination(a, b, character->s_player->getPosition());

	//上に乗った時
	if(HitFlag == up)
	{
		GameManager::PlayerSpd.y = 0.0f;
		//埋まった分を押し出す
		GameManager::PlayerPos.y = GameManager::SlopePosY;
		////
		//character->stopAllActions();
	}
	//下からぶつかったとき
	else if (HitFlag == under)
	{
		////ジャンプアクションを止める
		character->s_player->stopAllActions();
		//埋まった分を押し出す
		GameManager::PlayerPos.y = GameManager::SlopePosY;
	}


}
