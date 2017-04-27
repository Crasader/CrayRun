/***************************************************************************
*|
*|	概要　　リザルトレイヤー
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "CharacterLayer.h"
#include "Manager.h"
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

	String* b = String::createWithFormat("%i", a);
	n = Label::createWithSystemFont(b->getCString(), "arial", 60);
	n->setScale(4.0f);
	n->setPosition(300, 200);
	this->addChild(n);
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
	JumpInvestigate();
	n->setString(StringUtils::toString(a));
	n->setPosition(GameManager::PlayerPos);
}


/***************************************************************************
*|	概要　	タッチ時に呼び出される
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{	


	for (auto &item : touches)
	{
		//タッチのアドレスを格納する
		auto touch = item;
	
		if (GameManager::FirstTouchFlag == false)
		{
			
			//最初のタッチが呼ばれたら真
			//次のタッチまでのカウントを始める
			GameManager::FirstTouchFlag = true;
			
		}
		else
		{
			//最初のタッチフラグを偽にする
			GameManager::FirstTouchFlag = false;
			//最初のタッチカウントを初期化する
			GameManager::FirstTouchCnt = 0;
		}
		


	
	}
	log("onTouchesBegan");
	
}

/***************************************************************************
*|	概要　	スワイプ時に呼び出される
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesMoved");
	for (auto &item : touches)
	{
		auto touch = item;
		a = touch->getID();
		
	}

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

	Vector<Vec2>::iterator Iterator;
	//床の数だけループ
	for (Iterator = GameManager::FloorPos.begin(); Iterator != GameManager::FloorPos.end(); ++Iterator)
	{
		Vec2 vec = *Iterator;
		switch (GameManager::CollisionDetermination
		(vec, GameManager::LAYRE_SIZE,
			GameManager::PlayerPos, GameManager::PlayerSize))
		{
		case right:
			GameManager::PlayerPos.x = vec.x + GameManager::LAYRE_SIZE.x + GameManager::PlayerSize.x / 2 + 1;
			GameManager::PlayerSpd.x = 0.0f;
			break;
		case left:
			/*GameManager::PlayerPos.x = GameManager::FloorPosx[i] - GameManager::PlayerSize.x / 2;*/
			GameManager::RightFlag = true;
			GameManager::PlayerSpd.x = -6.0f;
			break;
		case up:
			GameManager::PlayerPos.y = vec.y;
			GameManager::PlayerSpd.y = 0.0f;
			//ジャンプ可能にする
			GameManager::JumpFlag = true;
			break;
		/*case under:
			GameManager::PlayerPos.y = GameManager::FloorPosy[i] - GameManager::LAYRE_SIZE.y - GameManager::PlayerSize.y - 1;
			GameManager::PlayerSpd.y = 0.0f;
			break;*/
		 default:
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
		//ジャンプ可能にする
		GameManager::JumpFlag = true;

	}



}

/***************************************************************************
*|	概要　	ジャンプするか調べる
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::JumpInvestigate()
{

	//最初のタッチフラグが真なら
	if (GameManager::FirstTouchFlag == true)
	{
		GameManager::FirstTouchCnt++;
	}
	//一回目のタッチから1秒以上経過したなら

	if (GameManager::FirstTouchCnt > 4)
	{
		//ジャンプ関数を呼ぶ
		character->Jump();
		//最初のタッチフラグを偽にする
		GameManager::FirstTouchFlag = false;
		//最初のタッチカウントを初期化する
		GameManager::FirstTouchCnt = 0;
	}
}
