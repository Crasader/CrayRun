/***************************************************************************
*|
*|	概要　　キャラクターレイヤー
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "CharacterLayer.h"

USING_NS_CC;


/* ---- 名前空間を解放 -------------------- */
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

	//デバック
	String* b = String::createWithFormat("%i", a);
	n = Label::createWithSystemFont(b->getCString(), "arial", 60);
	n->setScale(4.0f);
	n->setPosition(300, 200);
	this->addChild(n);

	int FirstTouchCnt = 0;//最初のタッチからどれだけ経過したか
	//bool FirstTouchFlag = false;//最初のタッチが呼ばれたか

	
	
	return true;
}

/***************************************************************************
*|	概要　	毎フレーム呼び出す
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::update(float date)
{
	//金型が変更されている場合
	if (GameManager::ChangeMold == true) {
		//型を変更する
		ChangeMold();
	}

	//移動する
	character->Move();
	//重力
	character->Gravity();
	//何番目のマップにいるか求める
	character->GetLoopPos();


	//プレイヤーと床の衝突判定
	CollisionResponseFloor();
	if(GameManager::Mold != Gnome)
	//プレイヤーと粘土床の衝突判定
	CollisionResponseCrayFloor();
	//プレイヤーと斜面のあたり判定
	CollisionResponseSlope();
	//ジャンプするか調べる
	JumpInvestigate();


	n->setString(StringUtils::toString(a));
	n->setPosition(GameManager::PlayerPos);

	//サイズ変更
	character->setScale();

	n->setString(StringUtils::toString(b));
	n->setPosition(GameManager::PlayerPos + Vec2(300, 0));

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
	
		if (FirstTouchFlag == false)
		{
			
			//最初のタッチが呼ばれたら真
			//次のタッチまでのカウントを始める
			FirstTouchFlag = true;
			
		}
		else
		{
			//最初のタッチフラグを偽にする
			FirstTouchFlag = false;
			//最初のタッチカウントを初期化する
			FirstTouchCnt = 0;
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
		//キャラクターのマルチタッチ判定
		MultiTouchCharacter();

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
*|	概要　	キャラクターのマルチタッチ判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::MultiTouchCharacter()
{
	//タッチが当たった方向
	Direction m_touch_collision_direction[EFFECTIVENESS_TOUCH];
	//タッチがキャラクターに当たったか
	bool m_touch_collision[EFFECTIVENESS_TOUCH];

	//タッチがプレイヤーに当たったか
	m_touch_collision[0] = GameManager::HitJudgment(
		touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
		GameManager::PlayerPos, GameManager::PlayerSize);
	//タッチ2がプレイヤーに当たったか
	m_touch_collision[1] = GameManager::HitJudgment(
		touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
		GameManager::PlayerPos, GameManager::PlayerSize);

	//タッチが二つともプレイヤーに当たったか
	if (m_touch_collision[0] == true && m_touch_collision[1] == true)
	{
		//タッチとプレイヤーのあたり判定
		m_touch_collision_direction[0] = GameManager::CollisionDetermination2(
			touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			GameManager::PlayerPos, GameManager::PlayerSize);

		//タッチ2とプレイヤーのあたり判定
		m_touch_collision_direction[1] = GameManager::CollisionDetermination2(
			touchpos[1] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			GameManager::PlayerPos, GameManager::PlayerSize);


		//上下に挟んでいるかつもとの大きさの場合
		if (m_touch_collision_direction[0] == up || m_touch_collision_direction[1] == under || m_touch_collision_direction[0] == under || m_touch_collision_direction[1] == up && character->isScaleY == false)
		{
			//大きさ変更
			GameManager::PlayerSize.y = 32.0f;
			if(GameManager::Mold != Slime)
			character->isScaleY = true;
		}
		//左右に挟んでいるかつ元の大きさの場合
		else if (m_touch_collision_direction[0] == left || m_touch_collision_direction[1] == left || m_touch_collision_direction[0] == right || m_touch_collision_direction[1] == right && character->isScaleX == false)
		{
			//大きさ変更
			GameManager::PlayerSize.x = 32;
			if (GameManager::Mold != Slime)
				character->isScaleX = true;
		}
	}
}



//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//
//概要：金型によるキャラクタの変更
//
//引数：なし
//
//戻り値：なし
//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

void CharacterLayer::ChangeMold()
{
		switch (GameManager::Mold)
		{
		case Normal:
			character->removeFromParent();
			character = Character::create();
			//変更したので戻す
			GameManager::ChangeMold = false;
			break;
		case Rabbit:
			character->removeFromParent();
			character = Rabbit::create();
			//変更したので戻す
			GameManager::ChangeMold = false;
			break;
		case Gnome:
			//変更したので戻す
			character->removeFromParent();
			character = Gnome::create();
			GameManager::ChangeMold = false;
			break;
		case Phoenix:
			//変更したので戻す
			character->removeFromParent();
			character = Phoenix::create();
			GameManager::ChangeMold = false;
			break;
		case Slime:
			character->removeFromParent();
			character = Slime::create();
			//変更したので戻す
			GameManager::ChangeMold = false;
			break;
		}
		//変更したのでaddChildする
		this->addChild(character);

		status = Status::create();
		addChild(status);
}





/***************************************************************************
*|	概要　	プレイヤーと床の衝突判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::CollisionResponseFloor()
{

	std::vector<Vec2>::iterator Iterator;

	//////マップの数だけループ
		//床の数だけループ
		for (Iterator = GameManager::AllFloorPos[GameManager::PlayerMapPos].begin(); Iterator != GameManager::AllFloorPos[GameManager::PlayerMapPos].end(); ++Iterator)
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
				/*GameManager::PlayerPos.x = GameManager::AllFloorPosx[i] - GameManager::PlayerSize.x / 2;*/
				GameManager::RightFlag = true;
				GameManager::PlayerSpd.x = -6.0f;
				break;
			case up:
				GameManager::PlayerPos.y = vec.y;
				GameManager::PlayerSpd.y = 0.0f;
				//ジャンプ可能にする
				GameManager::JumpCnt = 0;
				GameManager::JumpFlag = true;
				break;
				/*case under:
				GameManager::PlayerPos.y = GameManager::AllFloorPosy[i] - GameManager::LAYRE_SIZE.y - GameManager::PlayerSize.y - 1;
				GameManager::PlayerSpd.y = 0.0f;
				break;*/
			default:
				break;

				}
		}	
}

/***************************************************************************
*|	概要　	プレイヤーと粘土床の衝突判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::CollisionResponseCrayFloor()
{
	std::vector<Vec2>::iterator Iterator;
	std::vector<Vec2>::iterator IteratorSize;
	//ループした回数
	int g_loop_cnt = 0;
	//////マップの数だけループ
//	b = GameManager::CrayFloorSize[g_loop_cnt].y;

	//床の数だけループ
	for (Iterator = GameManager::AllCrayFloorPos[GameManager::PlayerMapPos].begin(); Iterator != GameManager::AllCrayFloorPos[GameManager::PlayerMapPos].end(); ++Iterator)
	{
		//イテレーターに最初の要素を教える
		IteratorSize = GameManager::CrayFloorSize.begin();
		//何個目を見ればいいか教える
		IteratorSize += g_loop_cnt;
		
		if (IteratorSize == GameManager::CrayFloorSize.end())
		{
			GameManager::CrayFloorSize.insert(GameManager::CrayFloorSize.begin() + g_loop_cnt, Vec2(192, 320));
			//GameManager::CrayFloorSize[g_loop_cnt] = Vec2(192, 320);
		}
		//イテレーターに最初の要素を教える
		IteratorSize = GameManager::CrayFloorSize.begin();
		//何個目を見ればいいか教える
		IteratorSize += g_loop_cnt;

		Vec2 vec = *Iterator;
		switch (GameManager::CollisionDetermination
		(vec + Vec2( GameManager::MAX_CRAYSTAGESIZE.x / 2 - (*IteratorSize).x / 2, -(GameManager::MAX_CRAYSTAGESIZE.y - (*IteratorSize).y)),(*IteratorSize),
			GameManager::PlayerPos, GameManager::PlayerSize))
		{
		case right:
			GameManager::PlayerPos.x = vec.x + GameManager::MAX_CRAYSTAGESIZE.x  -  (*IteratorSize).x / 2 - GameManager::PlayerSize.x / 2;
			GameManager::PlayerSpd.x = 0.0f;
			b = 1;
			break;
		case left:
			GameManager::PlayerPos.x = vec.x + GameManager::MAX_CRAYSTAGESIZE.x / 2 - (*IteratorSize).x / 2 - GameManager::PlayerSize.x / 2;
			GameManager::RightFlag = true;
			GameManager::PlayerSpd.x = -6.0f;
			b = 2;
			break;
		case up:
			b = (*IteratorSize).y;
			GameManager::PlayerPos.y = vec.y  - GameManager::MAX_CRAYSTAGESIZE.y + (*IteratorSize).y;
			GameManager::PlayerSpd.y = 0.0f;
			//ジャンプ可能にする
			GameManager::JumpCnt = 0;
			GameManager::JumpFlag = true;
		
			break;
			case under:
			//GameManager::PlayerPos.y = GameManager::AllFloorPosy[i] - GameManager::LAYRE_SIZE.y - GameManager::PlayerSize.y - 1;
			//GameManager::PlayerSpd.y = 0.0f;
			break;
		default:
			break;

		}
		//カウントを増やす
		g_loop_cnt++;
	}
}

/***************************************************************************
*|	概要　	プレイヤーと斜面の衝突判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::CollisionResponseSlope()
{
	for (int i = 0; i <= GameManager::MapLoopCnt; i++)
	{

		//最初の斜面右端を格納する
		IteratorLeft = GameManager::AllLeftPos[i].begin();
		//vectorの数だけループ
		for (IteratorRight = GameManager::AllRightPos[i].begin(); IteratorRight != GameManager::AllRightPos[i].end(); ++IteratorRight)
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
				GameManager::JumpCnt = 0;
				GameManager::JumpFlag = true;

			}
			IteratorLeft++;
		}

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
	if (FirstTouchFlag == true)
	{
		FirstTouchCnt++;
	}
	//一回目のタッチから1秒以上経過したなら

	if (FirstTouchCnt > 4)
	{
		//ジャンプ関数を呼ぶ
		character->Jump();
		//最初のタッチフラグを偽にする
		FirstTouchFlag = false;
		//最初のタッチカウントを初期化する
		FirstTouchCnt = 0;
	}
}
