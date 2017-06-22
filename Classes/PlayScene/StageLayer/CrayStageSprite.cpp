/***************************************************************************
*|
*|	概要　コインクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "CrayStageSprite.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace std;
/***************************************************************************
*|	概要　　初期化処理
*|	引数　　画像名、左右頂点の座標
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool CrayStageSprite::init(std::string filename)
{
	if (!Sprite::initWithFile(filename)) {

		return false;
	}
	//初期化
	m_size = MAX_SIZE;

	m_flame_cnt = 0;
	m_time = 0;
	// Register Touch Event
	EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();

	//listener->onTouchesBegan = CC_CALLBACK_2(CrayStageSprite::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(CrayStageSprite::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(CrayStageSprite::onTouchesEnded, this);
	//listener->onTouchesCancelled = CC_CALLBACK_2(CrayStageSprite::onTouchesCancelled, this);

	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//_touchListener = listener;
	hit_flag = true;

	//毎フレーム呼ぶ
	this->scheduleUpdate();

	return true;
}


/***************************************************************************
*|	概要　　スプライトを作成する。
*|	引数　	画像名、左右の座標頂点
*|　戻り値　シーンのアドレス
****************************************************************************/
CrayStageSprite* CrayStageSprite::create(string filename)
{
	//メモリ確保
	CrayStageSprite *pRet = new(nothrow)CrayStageSprite();

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





void CrayStageSprite::update(float data)
{
	this->setScale(m_size.x / MAX_SIZE.x, m_size.y / MAX_SIZE.y);

	//ノームはこの処理を無視する
	if (GameManager::Mold != GameManager::Gnome) {
		//プレイヤーと粘土床の衝突判定
		CollisionPlayer();
	}

	//
	//if (m_leap_flag) {
	//	
	//	if (m_size.y < 32)
	//	{
	//		m_leap_flag = false;
	//	}
	//	m_size.y -= 10;
	//}
	//ゲームが始まってからのフレーム数
	//m_flame_cnt++;
}



/***************************************************************************
*|	概要　	プレイヤーと粘土床の衝突判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CrayStageSprite::CollisionPlayer()
{
	
	switch (GameManager::CollisionDetermination
	(Vec2(this->getPosition().x, this->getPosition().y +  m_size.y), (m_size),
		GameManager::PlayerPos, GameManager::PlayerSize))
	{
	case GameManager::right:
		//GameManager::PlayerPos.x = this->getPosition().x /*+ MAX_SIZE.x - m_size.x / 2*/ - GameManager::PlayerSize.x / 2;
		//GameManager::PlayerSpd.x = 0.0f;
		break;
	case GameManager::left:
		
		
			GameManager::GameOverFlag = true;
		

		////当たったので潰れる
		//character->s_player->setAnchorPoint(Vec2(0, 0));
		//GameManager::PlayerSize.x = 32;
		//GameManager::PlayerPos.x += 96;
		break;
	case GameManager::up:
		if (!GameManager::JumpState)
		{
			GameManager::PlayerPos.y = this->getPosition().y + m_size.y;
			GameManager::PlayerSpd.y = 0.0f;
			//ジャンプ可能にする
			GameManager::JumpCnt = 0;
			GameManager::JumpFlag = true;
		}

		break;
	case GameManager::under:
		
			GameManager::PlayerPos.y = this->getPosition().y/* - MAX_SIZE.y*/ - GameManager::PlayerSize.y - 2;
			GameManager::PlayerSpd.y = 0.0f;		
		break;
	default:
		break;

	}

	
}

/***************************************************************************
*|	概要　	スワイプされたとき
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CrayStageSprite::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesMoved");

	//タッチID格納
	int g_touch_id;

	//タッチの数だけループ
	for (auto &item : touches)
	{
		//タッチのIDを取得する
		auto touch = item;
		//タッチID取得
		g_touch_id = touch->getID();

		//3つ目以上のタッチは受け付けない
		if (g_touch_id < EFFECTIVENESSTOUCH)
		{
			//座標を取得する
			touchpos[g_touch_id] = touch->getLocation();
			touchpos[g_touch_id].x += GameManager::m_cameraposx - 480;
		}
	}


	//二回以上タッチされたら
	if (g_touch_id >= 1)
	{
		MultiTouchCrayStage();
		
	}



}

/***************************************************************************
*|	概要	離されたとき
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CrayStageSprite::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	////初期化する
	//for (int i = 0; i < EFFECTIVENESSTOUCH; i++)
	//{
	//	touchpos[i] = Vec2(0.0f, 0.0f);
	//	old_touchpos[i] = Vec2(0.0f, 0.0f);
	//}

}




/***************************************************************************
*|	概要	二つの指が当たっているか求める
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CrayStageSprite::MultiTouchCrayStage()
{
	log("######   multi");
	//有効なタッチの数
	const int EFFECTIVENESSTOUCH = 2;

	//タッチがキャラクターに当たったか
	bool m_touch_collision[EFFECTIVENESSTOUCH];

	//タッチがプレイヤーに当たったか
	m_touch_collision[0] = GameManager::HitJudgment(
		touchpos[GameManager::First]/* - Vec2(GameManager::TOUCH_SIZE.x / 2, -GameManager::TOUCH_SIZE.y / 2)*/,Vec2(0.0f,0.0f)/* GameManager::TOUCH_SIZE*/,
		getPosition() + Vec2(m_size.x, 0), m_size);

	//タッチ2がプレイヤーに当たったか
	m_touch_collision[1] = GameManager::HitJudgment(
		touchpos[GameManager::Second] /*- Vec2(GameManager::TOUCH_SIZE.x / 2, -GameManager::TOUCH_SIZE.y / 2)*/, Vec2(0.0f, 0.0f),
		getPosition() + Vec2(m_size.x, 0), m_size);



	//タッチが二つとも当たったか
	if (m_touch_collision[0] == true && m_touch_collision[1] == true)
	{
		m_size.y= 32;
		DirectionJudgment();
	}
}



/***************************************************************************
*|	概要	上下か左右どちらに小さくなるか求める
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CrayStageSprite::DirectionJudgment()
{

	//前フレームもこの関数を通ったか
	//if (!hit_flag)
	//{
	//	float DistanceX[EFFECTIVENESSTOUCH];
	//	float total_distanceX = 0;
	//	for (int i = 0; i < EFFECTIVENESSTOUCH; i++)
	//	{
	//		//左右にどれだけ動いたか
	//		DistanceX[i] = abs(old_touchpos[i].x - touchpos[i].x);
	//		total_distanceX += DistanceX[i];
	//	}

	//	float DistanceY[EFFECTIVENESSTOUCH];
	//	float total_distanceY = 0;
	//	for (int i = 0; i < EFFECTIVENESSTOUCH; i++)
	//	{
	//		//上下にどれだけ動いたか
	//		DistanceY[i] = abs(old_touchpos[i].y - touchpos[i].y);
	//		total_distanceY += DistanceY[i];
	//	}

		//プレイヤが左右上下どちらに挟もうとしたか
		//左右なら
		//if (total_distanceX >= total_distanceY)
		{
			//m_size.x -= total_distanceX;

			/*m_size.y = 32;*/
			
		}
	/*	m_leap_flag = true;
		m_time = m_flame_cnt;
		hit_flag = true;*/
		/*	else
		{

				m_size.y -= total_distanceY;

		}
*/
//更新処理
	/*	old_touchpos[GameManager::First] = touchpos[GameManager::First];
		old_touchpos[GameManager::Second] = touchpos[GameManager::Second];*/
		//}
		//前フレーム通ってないとき
		//else
		//{
		//	//更新処理
		//	old_touchpos[GameManager::First] = touchpos[GameManager::First];
		//	old_touchpos[GameManager::Second] = touchpos[GameManager::Second];
			//hit_flag = true;
		//}
	//}
}





