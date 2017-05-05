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
	log("############################### CHARsCTERLAYER created");

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
	//ジャンプするか調べる
	JumpInvestigate();
	////プレイヤーのサイズ
	if (GameManager::PlayerSize.x < character->PLAYER_MAX_SIZE)
	{
		GameManager::PlayerSize.x += 0.1f;
	}
	else if (GameManager::PlayerSize.x > character->PLAYER_MAX_SIZE)
	{
		GameManager::PlayerSize.x = 32.0f;
	}


	if (GameManager::PlayerSize.y < character->PLAYER_MAX_SIZE)
	{
		GameManager::PlayerSize.y += 0.1;
	}
	else if (GameManager::PlayerSize.y > character->PLAYER_MAX_SIZE)
	{
		GameManager::PlayerSize.y = 32.0f;
	}

	character->s_player->setScale(GameManager::PlayerSize.x / character->PLAYER_MAX_SIZE, GameManager::PlayerSize.y / character->PLAYER_MAX_SIZE);
	n->setString(StringUtils::toString(GameManager::PlayerSize.y));
	n->setPosition(GameManager::PlayerPos + Vec2(500, 0));
	
	//n->setString(StringUtils::toString(b));
	//n->setPosition(GameManager::PlayerPos + Vec2(300, 0));

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
	//タッチの数だけループ
	for (auto &item : touches)
	{
		//タッチのIDを取得する
		auto touch = item;
		m_touch_id = touch->getID();
	
		//3つ目以上のタッチは受け付けない
		if (m_touch_id < 2)
		{
			//座標を取得する
			touchpos[m_touch_id] = touch->getLocation();
			touchpos[m_touch_id].x += GameManager::m_cameraposx - 480;
		}
	}


	//二回以上タッチされたら
	if (m_touch_id >= 1)
	{
	
		//タッチとプレイヤーのあたり判定
		m_touch_collision_direction[0] = GameManager::CollisionDetermination2(
			touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			GameManager::PlayerPos, GameManager::PlayerSize);
		
		//タッチ2とプレイヤーのあたり判定
		m_touch_collision_direction[1] = GameManager::CollisionDetermination2(
			touchpos[1] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			GameManager::PlayerPos, GameManager::PlayerSize);

	

		//上下でプレイヤーを挟んだ時
		if (m_touch_collision_direction[0] == up && m_touch_collision_direction[1] == under)
		{
		
		/*	b = 3;
			GameManager::PlayerSize.y = touchpos[1].y - touchpos[0].y;*/
			GameManager::PlayerSize.y = 32.0f;
		}
		else if(m_touch_collision_direction[0] == under && m_touch_collision_direction[1] == up)
		{
			
			b = 2;
			//GameManager::PlayerSize.y = touchpos[0].y - touchpos[1].y;
			GameManager::PlayerSize.y = 32.0f;
		}
		//左右でプレイヤーを挟んだ時
		if ((m_touch_collision_direction[0] == left && m_touch_collision_direction[1] == right)
			|| (m_touch_collision_direction[0] == right && m_touch_collision_direction[1] == left))
		{
			GameManager::PlayerSize.x = 30;
		}
		else if ((m_touch_collision_direction[1] == left && m_touch_collision_direction[0] == right)
			|| (m_touch_collision_direction[1] == right && m_touch_collision_direction[0] == left))
		{
			GameManager::PlayerSize.x = 30;
		}
		//初期化する
		touchpos[0] = Vec2(0.0f, 0.0f);
		touchpos[1] = Vec2(0.0f, 0.0f);
	
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
	//最初の斜面右端を格納する
	IteratorLeft = GameManager::LeftPos.begin();
	//vectorの数だけループ
	for (IteratorRight = GameManager::RightPos.begin(); IteratorRight != GameManager::RightPos.end();  ++IteratorRight)
	{
		//衝突判定（斜面）
		Direction HitFlag = GameManager::DiagonalCollisionDetermination(*IteratorLeft, *IteratorRight, GameManager::PlayerPos/*character->s_player->getPosition()*/);
		//上に乗った時
		if (HitFlag == up)
		{
			GameManager::PlayerSpd.y = 0.0f;
			//埋まった分を押し出す
			GameManager::PlayerPos.y = GameManager::SlopePosY;
			//ジャンプ可能にする
			GameManager::JumpFlag = true;

		}
		IteratorLeft++;
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
