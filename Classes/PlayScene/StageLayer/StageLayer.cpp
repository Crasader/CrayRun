/***************************************************************************
*|
*|	概要　　ステージレイヤー
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "StageLayer.h"
#include "../../GameManager.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
//using namespace std;
bool StageLayer::init()
{
	if (!Layer::init()) {

		return false;

	}
	/////////マップ描画////////

	//タイルマップの読み込み
	//マップチップ
	GameManager::map.push_back(TMXTiledMap::create("map1.tmx"));
	IteratorMap = GameManager::map.begin();
	TMXTiledMap* g_Map = *IteratorMap;
	//タイルマップの中心座標を設定
	g_Map->setAnchorPoint(Vec2(0, 0));
	//タイルマップの座標設定
	g_Map->setPosition(Point(0, 0));
	//画像の描画
	this->addChild(g_Map);
	//レイヤーにノードを集約
	craystage.push_back(CrayStage::create());
	ItratorCrayStage=craystage.begin();
	this->addChild((*ItratorCrayStage));
	//レイヤーにノードを集約
	stage = Stage::create();
	this->addChild(stage);
	//レイヤーにノードを集約
	coin.push_back(Coin::create());
	IteratorCoin = coin.begin();
	this->addChild(*IteratorCoin);
	//レイヤーにノードを集約
	slope.push_back(Slope::create());
	IteratorSlope = slope.begin();
	this->addChild(*IteratorSlope);
	//レイヤーにノードを集約
	mold.push_back(Mold::create());
	this->addChild(mold[GameManager::MapLoopCnt]);
	//レイヤーにノードを集約
	needle.push_back(Needle::create());
	ItratorNeedle = needle.begin();
	this->addChild((*ItratorNeedle));
	//敵生成
	enemy.push_back(Enemy::create());
	this->addChild(enemy[0]);
	//this->addChild(*(needle.begin()));
	//this->addChild(needle[GameManager::MapLoopCnt]);
	// Register Touch Event
	EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(StageLayer::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(StageLayer::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(StageLayer::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(StageLayer::onTouchesCancelled, this);

	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//_touchListener = listener;

	m_data = 0;


	//デバック
	String* b = String::createWithFormat("%i", a);
	n = Label::createWithSystemFont(b->getCString(), "arial", 60);
	n->setScale(4.0f);
	n->setPosition(300, 200);
	this->addChild(n);



	this->scheduleUpdate();

	return true;

}


/***************************************************************************
*|	概要　　毎フレーム呼ばれる
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void StageLayer::update(float data) 
{
	n->setString(StringUtils::toString(b));
	n->setPosition(GameManager::PlayerPos);

	Vector<Vec2>::iterator Iterator;
	int i = 0;
	////床の数だけループ
	//for (Iterator = GameManager::MoldPos.begin(); Iterator != GameManager::MoldPos.end(); ++Iterator)
	//{
	//	Node* q = mold->getChildByTag(i);
	//	Vec2 vec = *Iterator;
	//	vec += GameManager::MoldSpd;
	//	q->setPosition(vec);
	//	i++;
	//}

	//粘土床のサイズ変更
	Vector<Vec2>::iterator g_sizeitertor;
	for (g_sizeitertor = craystage[GameManager::PlayerMapPos]->CrayStageSize.begin(); g_sizeitertor != craystage[GameManager::PlayerMapPos]->CrayStageSize.end();++g_sizeitertor)
	{
		ItratorCrayStage = craystage.begin();
		ItratorCrayStage += GameManager::PlayerMapPos;
		Vector<Sprite*>::iterator SpriteIterator;
		SpriteIterator = (*ItratorCrayStage)->crayfloor.begin();
		SpriteIterator += GameManager::CraySizeChangeCnt;
		(*SpriteIterator)->setScale((*g_sizeitertor).x / GameManager::MAX_CRAYSTAGESIZE.x  , (*g_sizeitertor).y / GameManager::MAX_CRAYSTAGESIZE.y);

	}

	//コインあたり判定
	CollisionResponseCoin();
	//金型当たり判定
	HittingMold();
	//針当たり判定
	HittingNeedle();
	//敵とプレイヤの当たり判定
	HittingEnemy();

	if (static_cast<int>(GameManager::m_cameraposx + 480 ) % static_cast<int>(GameManager::MAP_SIZE.x) == 0)
	{
		//マップ生成
		MapCreate();
		if (GameManager::MapLoopCnt > 2)
		{
			//マップ削除
			MapDelete();
		}

	}

	
		GameManager::CrayFloorSize = craystage[GameManager::PlayerMapPos]->CrayStageSize;
	
}

/***************************************************************************
*|	概要　  ステージ生成
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void StageLayer::MapCreate()
{
	GameManager::MapLoopCnt++;
	//タイルマップの読み込み
	//マップチップ
	GameManager::map.push_back(TMXTiledMap::create("floor.tmx"));
	IteratorMap = GameManager::map.begin();
	IteratorMap += GameManager::MapLoopCnt;
//	TMXTiledMap* g_Map = *IteratorMap;
	//タイルマップの中心座標を設定
	(*IteratorMap)->setAnchorPoint(Vec2(0, 0));
	//タイルマップの座標設定
	(*IteratorMap)->setPosition(Point(GameManager::m_cameraposx + 480, 0));
	//画像の描画
	this->addChild((*IteratorMap));
	//粘土床
	craystage.push_back(CrayStage::create());
	//イテレータに粘土床の最初の要素を格納する
	ItratorCrayStage = craystage.begin();
	//ループさせたマップの数を見る
	ItratorCrayStage+= GameManager::MapLoopCnt;
	this->addChild((*ItratorCrayStage));

	//ステージ座標を取得
	stage->init();

	//vectorにコインオブジェクトのアドレスを格納する
	coin.push_back(Coin::create());
	//イテレータにコインの最初の要素を格納する
	IteratorCoin = coin.begin();
	//ループさせたマップの数を見る
	IteratorCoin += GameManager::MapLoopCnt;
	this->addChild(*IteratorCoin);



	//斜面座標を取得
	slope.push_back(Slope::create());
	IteratorSlope = slope.begin();
	IteratorSlope += GameManager::MapLoopCnt;
	this->addChild(*IteratorSlope);


	//金型作成
	mold.push_back(Mold::create());
	this->addChild(mold[GameManager::MapLoopCnt]);

	//針
	needle.push_back(Needle::create());
	this->addChild(needle[GameManager::MapLoopCnt]);

	//敵
	enemy.push_back(Enemy::create());
	this->addChild(enemy[GameManager::MapLoopCnt]);
}
/***************************************************************************
*|	概要  　ステージ削除　
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void StageLayer::MapDelete()
{
	//マップの削除
	IteratorMap = GameManager::map.begin();
	IteratorMap += GameManager::MapLoopCnt - 2;
	(*IteratorMap)->removeFromParent();
	//ステージの削除
	GameManager::AllFloorPos[GameManager::MapLoopCnt - 2].crend();
	//斜面ノードの削除
	IteratorSlope -= 2;
	Slope* g_slope = *IteratorSlope;
	g_slope->removeFromParent();

	////粘土床の削除
	//ItratorCrayStage -= 2;
	//CrayStage* g_craystage = *ItratorCrayStage;
	//g_craystage->removeFromParent();
	//craystage[GameManager::MapLoopCnt - 2]->removeFromParent();
	//粘土床座標の削除
	GameManager::AllCrayFloorPos[GameManager::MapLoopCnt - 2].crend();

	//斜面座標の削除
	GameManager::AllLeftPos[GameManager::MapLoopCnt - 2].crend();
	GameManager::AllRightPos[GameManager::MapLoopCnt - 2].crend();
	//コイン削除

	//金型削除
	mold[GameManager::MapLoopCnt - 2]->removeFromParent();
	//coin[GameManager::MapLoopCnt - 2]->removeFromParent();

	//針削除
	needle[GameManager::MapLoopCnt - 2]->removeFromParent();

	//敵削除
	enemy[GameManager::MapLoopCnt - 2]->removeFromParent();
}



/***************************************************************************
*|	概要　　コインあたり判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void StageLayer::CollisionResponseCoin()
{
	//コインレイヤーの数だけループ
	//for (IteratorCoin = coin.begin(); IteratorCoin < coin.end(); ++IteratorCoin)
	//{
	int g_LoopCnt = 0;
	IteratorCoin = coin.begin();
	IteratorCoin += GameManager::PlayerMapPos;
		////コインのデータを一時的に保存する
		Coin* m_SaveCoin = *IteratorCoin;
		for (int i = 0; i < m_SaveCoin->m_CoinCnt; i++)
		{
			//ループした数番目のコインを取得
			Node* n_coin  = m_SaveCoin->getChildByTag(g_LoopCnt);
			if (n_coin != nullptr)
			{
				//プレイヤーとコインの当たり判定
				if (GameManager::HitJudgment
				(n_coin->getPosition(), n_coin->getContentSize(),
					GameManager::PlayerPos, GameManager::PlayerSize) == true)
				{
					//当たったコインを削除
					m_SaveCoin->getChildByTag(g_LoopCnt)->removeFromParent();
					//スコアにとったコインのポイントをたす
					GameManager::Score += GameManager::CoinPoint[g_LoopCnt] * GameManager::ScoreCorrection;
				}
			}
			//ループカウントをインクリメント
			g_LoopCnt++;
		}
}


////__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
////	概　要：金型あたり判定
////	引　数：無し
////　戻り値：無し
////__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
void StageLayer::HittingMold()
{


	if (mold[GameManager::MapLoopCnt]->s_Mold != nullptr)
	{
		//金型とプレイヤーが当たっているか
		if (GameManager::HitJudgment
		(mold[GameManager::MapLoopCnt]->s_Mold->getPosition(), mold[GameManager::MapLoopCnt]->SIZE,
			GameManager::PlayerPos, GameManager::PlayerSize) == true)
		{
			//当たった金型を削除
			//mold[GameManager::MapLoopCnt]->removeFromParent();
			//兎型のキャラクターに変更
			GameManager::Mold = mold[GameManager::MapLoopCnt]->m_kind;
			GameManager::ChangeMold = true;

 		}
	}
}

/***************************************************************************
*|	概要　  針とプレイヤの当たり判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void StageLayer::HittingNeedle()
{
	GameManager::GameOverFlag = false;
	//イテレーター
	Vector<Sprite*>::iterator IteratorNeedle;
	//ループした回数
	int loop_cnt = 0;
	//
	for (IteratorNeedle = needle[GameManager::PlayerMapPos]->s_needle.begin();
		IteratorNeedle != needle[GameManager::PlayerMapPos]->s_needle.end(); ++IteratorNeedle)
	{
		//針がとがっているか
		if (needle[GameManager::PlayerMapPos]->m_needle_state[loop_cnt] == true)
		{
			if (GameManager::HitJudgment(needle[GameManager::PlayerMapPos]->s_needle[loop_cnt]->getPosition() + Vec2(-GameManager::LAYRE_SIZE.x/ 2 , GameManager::LAYRE_SIZE.y / 2),
				GameManager::LAYRE_SIZE, GameManager::PlayerPos, GameManager::PlayerSize) == true)
			{
			//	ゲームオーバーにする
				GameManager::GameOverFlag = true;
			}
		}
		loop_cnt++;
	}


}



/***************************************************************************
*|	概要　タッチが動いたとき
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void StageLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
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
		if (g_touch_id < 2)
		{
			//座標を取得する
			touchpos[g_touch_id] = touch->getLocation();
			touchpos[g_touch_id].x += GameManager::m_cameraposx - 480;
		}
	}


	//二回以上タッチされたら
	if (g_touch_id >= 1)
	{
		//粘土床のマルチタッチ判定
		MultiTouchCrayStage();
		//針のマルチタッチ判定
		MultiTouchNeedle();
		//初期化する
		touchpos[0] = Vec2(0.0f, 0.0f);
		touchpos[1] = Vec2(0.0f, 0.0f);
	}


}

/***************************************************************************
*|	概要　	粘土床のマルチタッチ判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void StageLayer::MultiTouchCrayStage()
{
	//タッチが当たった方向
	Direction m_touch_collision_direction[EFFECTIVENESSTOUCH];
	//タッチがキャラクターに当たったか
	bool m_touch_collision[EFFECTIVENESSTOUCH];

	Vector<Vec2>::iterator Iterator;

	int g_loop_cnt = 0;
	for (Iterator = GameManager::AllCrayFloorPos[GameManager::PlayerMapPos].begin(); Iterator != GameManager::AllCrayFloorPos[GameManager::PlayerMapPos].end(); ++Iterator)
	{
		Vec2 g_craystage_size = craystage[GameManager::PlayerMapPos]->CrayStageSize[g_loop_cnt];

		//タッチがプレイヤーに当たったか
		m_touch_collision[0] = GameManager::HitJudgment(
			touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			(*Iterator) + Vec2(g_craystage_size.x / 2, -g_craystage_size.y), g_craystage_size);
		//タッチ2がプレイヤーに当たったか
		m_touch_collision[1] = GameManager::HitJudgment(
			touchpos[1] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			(*Iterator) + Vec2(g_craystage_size.x / 2, -g_craystage_size.y), g_craystage_size);

		//タッチが二つともプレイヤーに当たったか
		if (m_touch_collision[0] == true && m_touch_collision[1] == true)
		{
			//タッチとプレイヤーのあたり判定
			m_touch_collision_direction[0] = GameManager::CollisionDetermination2(
				touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
				(*Iterator) + Vec2(g_craystage_size.x / 2, -g_craystage_size.y), g_craystage_size);

			//タッチ2とプレイヤーのあたり判定
			m_touch_collision_direction[1] = GameManager::CollisionDetermination2(
				touchpos[1] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
				(*Iterator) + Vec2(g_craystage_size.x / 2, -g_craystage_size.y), g_craystage_size);



			//上に挟んだか
			if (m_touch_collision_direction[0] == up || m_touch_collision_direction[1] == under || m_touch_collision_direction[0] == under || m_touch_collision_direction[1] == up)
			{
				/*		int g_distanceY;
				if (touchpos[0].y - touchpos[1].y < 0)
				{
				g_distanceY = touchpos[1].y - touchpos[0].y;
				}
				else {
				g_distanceY = touchpos[0].y - touchpos[1].y;
				}*/

				//大きさ変更
				craystage[GameManager::PlayerMapPos]->CrayStageSize[g_loop_cnt].y = 32;
				GameManager::CrayFloorSize = craystage[GameManager::PlayerMapPos]->CrayStageSize;
			}
			//下に挟んだか
			else if (m_touch_collision_direction[0] == left || m_touch_collision_direction[1] == left || m_touch_collision_direction[0] == right || m_touch_collision_direction[1] == right)
			{
				//int g_distanceX;
				//if (touchpos[0].x - touchpos[1].x < 0)
				//{
				//	g_distanceX = touchpos[1].x - touchpos[0].x;
				//}
				//else
				//{
				//	g_distanceX = touchpos[0].x - touchpos[1].x;
				//}
				//大きさ変更
				craystage[GameManager::PlayerMapPos]->CrayStageSize[g_loop_cnt].x = 32;
				GameManager::CrayFloorSize = craystage[GameManager::PlayerMapPos]->CrayStageSize;
			}
		}

		g_loop_cnt++;
	}
}

/***************************************************************************
*|	概要　  針のマルチタッチ判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void StageLayer::MultiTouchNeedle()
{
	//タッチが当たった方向
	Direction m_touch_collision_direction[EFFECTIVENESSTOUCH];
	//タッチがキャラクターに当たったか
	bool m_touch_collision[EFFECTIVENESSTOUCH];

	Vector<Sprite*>::iterator Iterator;
	b = 1;
	int loop_cnt = 0;
	for (Iterator = needle[GameManager::PlayerMapPos]->s_needle.begin(); Iterator != needle[GameManager::PlayerMapPos]->s_needle.end(); ++Iterator)
	{
		b = 2;
		//Vec2 g_craystage_size = craystage[GameManager::PlayerMapPos]->CrayStageSize[loop_cnt];

		//タッチがプレイヤーに当たったか
		m_touch_collision[0] = GameManager::HitJudgment(
			touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), GameManager::PlayerSize,
			(*Iterator)->getPosition() + Vec2(GameManager::LAYRE_SIZE.x / 2, -GameManager::LAYRE_SIZE.y / 2), GameManager::LAYRE_SIZE);
		//タッチ2がプレイヤーに当たったか
		m_touch_collision[1] = GameManager::HitJudgment(
			touchpos[1] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), GameManager::PlayerSize,
			(*Iterator)->getPosition() + Vec2(GameManager::LAYRE_SIZE.x / 2, -GameManager::LAYRE_SIZE.y /2), GameManager::LAYRE_SIZE);

		//タッチが二つともプレイヤーに当たったか
		if (m_touch_collision[0] == true && m_touch_collision[1] == true)
		{
			
			//タッチとプレイヤーのあたり判定
			m_touch_collision_direction[0] = GameManager::CollisionDetermination2(
				touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
				(*Iterator)->getPosition() + Vec2(GameManager::LAYRE_SIZE.x / 2, -GameManager::LAYRE_SIZE.y), GameManager::LAYRE_SIZE);

			//タッチ2とプレイヤーのあたり判定
			m_touch_collision_direction[1] = GameManager::CollisionDetermination2(
				touchpos[1] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
				(*Iterator)->getPosition() + Vec2(GameManager::LAYRE_SIZE.x / 2, -GameManager::LAYRE_SIZE.y), GameManager::LAYRE_SIZE);
			b = (*Iterator)->getPosition().x;


			////挟んだか
			//if (m_touch_collision_direction[0] == up || m_touch_collision_direction[1] == under || m_touch_collision_direction[0] == under || m_touch_collision_direction[1] == up
			//	||m_touch_collision_direction[0] == left || m_touch_collision_direction[1] == left || m_touch_collision_direction[0] == right || m_touch_collision_direction[1] == right)
			//{
				b = 11111111;
				// 普通の画像から変更
				Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/needle2.png");
				(*Iterator)->setTexture(texture);
				needle[GameManager::PlayerMapPos]->m_needle_state[loop_cnt] = false;
		//	}

		}

		loop_cnt++;
	}

}

/***************************************************************************
*|	概要　  敵とプレイヤの当たり判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void StageLayer::HittingEnemy()
{
	std::vector<Vec2>::iterator IteratorEnemy;
	for (IteratorEnemy = enemy[GameManager::PlayerMapPos]->m_EnemyPos.begin(); IteratorEnemy != enemy[GameManager::PlayerMapPos]->m_EnemyPos.end(); ++IteratorEnemy)
	{
		switch (GameManager::CollisionDetermination
		((*IteratorEnemy), GameManager::LAYRE_SIZE,
			GameManager::PlayerPos, GameManager::PlayerSize))
		{
		case right:
			GameManager::PlayerPos.x = (*IteratorEnemy).x + GameManager::LAYRE_SIZE.x + GameManager::PlayerSize.x / 2 + 1;
			GameManager::PlayerSpd.x = 0.0f;
			GameManager::GameOverFlag = true;
			break;
		case left:
			/*GameManager::PlayerPos.x = GameManager::AllFloorPosx[i] - GameManager::PlayerSize.x / 2;*/
			GameManager::RightFlag = true;
			//GameManager::PlayerSpd.x = -6.0f;
			GameManager::GameOverFlag = true;
			break;
		case up:
			GameManager::PlayerPos.y = (*IteratorEnemy).y;
			GameManager::PlayerSpd.y =0.0f;
			//ジャンプ可能にする
		/*	character->GameManager::JumpCnt = 0;
			character->GameManager::JumpFlag = true;*/
			break;
			case under:
			//GameManager::PlayerPos.y = (*IteratorEnemy).y - ;
			GameManager::PlayerSpd.y = 0.0f;
			GameManager::GameOverFlag = true;
			break;
		default:
			break;

		}

	}
}
