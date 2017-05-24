/***************************************************************************
*|
*|	概要　　ステージレイヤー
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "../../GameManager.h"
#include "StageLayer.h"
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
	std::ostringstream MapName;

	MapName << "map" << rand() % MAX_MAP + 1 << ".tmx";

	//マップチップ
	GameManager::map.push_back(TMXTiledMap::create(MapName.str()));
	//GameManager::map.push_back(TMXTiledMap::create("TestMap.tmx"));

	IteratorMap = GameManager::map.begin();
	TMXTiledMap* g_Map = *IteratorMap;
	//タイルマップの中心座標を設定
	g_Map->setAnchorPoint(Vec2(0, 0));
	//タイルマップの座標設定
	g_Map->setPosition(Point(0, 0));
	//画像の描画
	this->addChild(g_Map);

	//粘土床
	craystage.push_back(CrayStage::create());
	ItratorCrayStage=craystage.begin();
	this->addChild((*ItratorCrayStage));
	//床
	stage = Stage::create();
	this->addChild(stage);
	//コイン作成
	coin.push_back(Coin::create());
	IteratorCoin = coin.begin();
	this->addChild(*IteratorCoin);
	//斜面生成
	slope.push_back(Slope::create());
	IteratorSlope = slope.begin();
	this->addChild(*IteratorSlope);
	//金型生成
	mold.push_back(Mold::create());
	this->addChild(mold[GameManager::MapLoopCnt]);
	//針生成
	needle.push_back(Needle::create());
	ItratorNeedle = needle.begin();
	this->addChild((*ItratorNeedle));

	// Register Touch Event
	EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(StageLayer::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(StageLayer::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(StageLayer::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(StageLayer::onTouchesCancelled, this);

	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//_touchListener = listener;


	////デバック
	//String* b = String::createWithFormat("%i", a);
	//n = Label::createWithSystemFont(b->getCString(), "arial", 60);
	//n->setScale(4.0f);
	//n->setPosition(300, 200);
	//this->addChild(n);

	DeleteCnt = 0;

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
	/*n->setString(StringUtils::toString(b));
	n->setPosition(GameManager::PlayerPos);*/

	Vector<Vec2>::iterator Iterator;
	int loop_cnt = 0;

		if (static_cast<int>(GameManager::m_cameraposx - 480) % static_cast<int>(GameManager::MAP_SIZE.x) == 0)
		{
			GameManager::MapLoopCnt++;
			//マップ生成
		//	MapCreate();
			//if (GameManager::MapLoopCnt > 5)
			//{
			//	//マップ削除
			//	MapDelete();
			//}
	}


	//粘土床のサイズ変更
	Vector<Vec2>::iterator g_sizeitertor;
	for (g_sizeitertor = craystage[GameManager::PlayerMapPos]->CrayStageSize.begin(); g_sizeitertor != craystage[GameManager::PlayerMapPos]->CrayStageSize.end();++g_sizeitertor)
	{
		ItratorCrayStage = craystage.begin();
		ItratorCrayStage += GameManager::PlayerMapPos;
		Vector<Sprite*>::iterator SpriteIterator;
		SpriteIterator = (*ItratorCrayStage)->crayfloor.begin();
		SpriteIterator += loop_cnt;
		(*SpriteIterator)->setScale((*g_sizeitertor).x / GameManager::MAX_CRAYSTAGESIZE.x  , (*g_sizeitertor).y / GameManager::MAX_CRAYSTAGESIZE.y);
		loop_cnt++;
	}

	//コインあたり判定
	CollisionResponseCoin();
	//金型当たり判定
	HittingMold();
	//針当たり判定
	HittingNeedle();
	


	
		GameManager::CrayFloorSize = craystage[GameManager::PlayerMapPos]->CrayStageSize;
	
}

/***************************************************************************
*|	概要　  ステージ生成
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void StageLayer::MapCreate()
{

	//タイルマップの読み込み
	
	std::ostringstream MapName;
	MapName << "map" << rand() % MAX_MAP + 1 << ".tmx";
	//マップチップ
	GameManager::map.push_back(TMXTiledMap::create(MapName.str()));
	//GameManager::map.push_back(TMXTiledMap::create("TestMap.tmx"));
	IteratorMap = GameManager::map.begin();
	IteratorMap += GameManager::MapLoopCnt;

//	TMXTiledMap* g_Map = *IteratorMap;
	//タイルマップの中心座標を設定
	GameManager::map[GameManager::MapLoopCnt]->setAnchorPoint(Vec2(0, 0));
	//タイルマップの座標設定
	GameManager::map[GameManager::MapLoopCnt]->setPosition(Point(GameManager::MAP_SIZE.x * GameManager::MapLoopCnt, 0));

	//画像の描画
	this->addChild(GameManager::map[GameManager::MapLoopCnt]);


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

}
/***************************************************************************
*|	概要  　ステージ削除　
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void StageLayer::MapDelete()
{
	//b = DeleteCnt;
	//マップの削除
	IteratorMap = GameManager::map.begin();
	IteratorMap += DeleteCnt;
	(*IteratorMap)->removeFromParent();


	//ステージの削除
	//std::remove(GameManager::AllFloorPos,DeleteCnt);
	//斜面ノードの削除
	IteratorSlope -= 3;
	Slope* g_slope = *IteratorSlope;
	g_slope->removeFromParent();
	g_slope = nullptr;
	////粘土床の削除
	//ItratorCrayStage -= 2;
	//CrayStage* g_craystage = *ItratorCrayStage;
	//g_craystage->removeFromParent();
	//craystage[GameManager::MapLoopCnt - 2]->removeFromParent();
	//粘土床座標の削除
	GameManager::AllCrayFloorPos[DeleteCnt].crend();

	//斜面座標の削除
	GameManager::AllLeftPos[DeleteCnt].crend();
	GameManager::AllRightPos[DeleteCnt].crend();
	//コイン削除

	//金型削除
	mold[DeleteCnt]->removeFromParent();
	mold[DeleteCnt] = nullptr;
	//coin[GameManager::MapLoopCnt - 2]->removeFromParent();

	//針削除
	needle[DeleteCnt]->removeFromParent();

	DeleteCnt++;
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
	//金型スプライトのイテレータ
	std::vector<Sprite*>::iterator IteratorMold;
	//ループした回数
	int loop_cnt = 0;
	for (IteratorMold = mold[GameManager::PlayerMapPos]->s_Mold.begin(); IteratorMold != mold[GameManager::PlayerMapPos]->s_Mold.end(); IteratorMold++)
	{
		if ((*IteratorMold) != nullptr)
		{
			//金型とプレイヤーが当たっているか
			if (GameManager::HitJudgment
			((*IteratorMold)->getPosition(), mold[GameManager::PlayerMapPos]->SIZE,
				GameManager::PlayerPos, GameManager::PlayerSize) == true)
			{
				//当たった金型を削除
				//mold[GameManager::MapLoopCnt]->removeFromParent();
				//兎型のキャラクターに変更
				GameManager::Mold = mold[GameManager::PlayerMapPos]->m_kind[loop_cnt];
				GameManager::ChangeMold = true;
			}
		}
		loop_cnt++;
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

	int loop_cnt = 0;
	for (Iterator = GameManager::AllCrayFloorPos[GameManager::PlayerMapPos].begin(); Iterator != GameManager::AllCrayFloorPos[GameManager::PlayerMapPos].end(); ++Iterator)
	{

		Vec2 craystage_size = craystage[GameManager::PlayerMapPos]->CrayStageSize[loop_cnt];

		//タッチがプレイヤーに当たったか
		m_touch_collision[0] = GameManager::HitJudgment(
			touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			(*Iterator) + Vec2(craystage_size.x, -craystage_size.y), craystage_size);
		//タッチ2がプレイヤーに当たったか
		m_touch_collision[1] = GameManager::HitJudgment(
			touchpos[1] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			(*Iterator) + Vec2(craystage_size.x / 2, -craystage_size.y), craystage_size);

		//タッチが二つともプレイヤーに当たったか
		if (m_touch_collision[0] == true && m_touch_collision[1] == true)
		{
			//タッチとプレイヤーのあたり判定
			m_touch_collision_direction[0] = GameManager::CollisionDetermination2(
				(*Iterator), GameManager::MAX_CRAYSTAGESIZE,
				touchpos[0], Vec2(0, 0));

			//タッチ2とプレイヤーのあたり判定
			m_touch_collision_direction[1] = GameManager::CollisionDetermination2(
				(*Iterator), GameManager::MAX_CRAYSTAGESIZE,
				touchpos[1], Vec2(0, 0));

	

			//上下に挟んだか
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
				craystage[GameManager::PlayerMapPos]->CrayStageSize[loop_cnt].y = 32;
				GameManager::CrayFloorSize = craystage[GameManager::PlayerMapPos]->CrayStageSize;
			

			}
			//左右に挟んだか
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
				craystage[GameManager::PlayerMapPos]->CrayStageSize[loop_cnt].x = 32;
				//GameManager::CrayFloorSize = craystage[GameManager::PlayerMapPos]->CrayStageSize;
			}
		}

		loop_cnt++;
	}
}

/***************************************************************************
*|	概要　  針のマルチタッチ判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void StageLayer::MultiTouchNeedle()
{
	////タッチが当たった方向
	//Direction m_touch_collision_direction[EFFECTIVENESSTOUCH];
	//タッチがキャラクターに当たったか
	bool m_touch_collision[EFFECTIVENESSTOUCH];

	//スプライト情報のイテレータ
	Vector<Sprite*>::iterator Iterator;

	Vec2 NeedleSizeneedle = needle[GameManager::PlayerMapPos]->SIZE;


	//ループした回数
	int loop_cnt = 0;
	for (Iterator = needle[GameManager::PlayerMapPos]->s_needle.begin(); Iterator != needle[GameManager::PlayerMapPos]->s_needle.end(); ++Iterator)
	{
		
		//Vec2 g_craystage_size = craystage[GameManager::PlayerMapPos]->CrayStageSize[loop_cnt];

		//タッチがプレイヤーに当たったか
		m_touch_collision[0] = GameManager::HitJudgment(
			touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			(*Iterator)->getPosition() + Vec2(NeedleSizeneedle.x / 2, -NeedleSizeneedle.y / 2), NeedleSizeneedle);
		//タッチ2がプレイヤーに当たったか
		m_touch_collision[1] = GameManager::HitJudgment(
			touchpos[1] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			(*Iterator)->getPosition() + Vec2(NeedleSizeneedle.x / 2, -NeedleSizeneedle.y /2), NeedleSizeneedle);

		//タッチが二つともプレイヤーに当たったか
		if (m_touch_collision[0] == true && m_touch_collision[1] == true)
		{
			
			////タッチとプレイヤーのあたり判定
			//m_touch_collision_direction[0] = GameManager::CollisionDetermination2(
			//	touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			//	(*Iterator)->getPosition() + Vec2(GameManager::LAYRE_SIZE.x / 2, -GameManager::LAYRE_SIZE.y), GameManager::LAYRE_SIZE);

			////タッチ2とプレイヤーのあたり判定
			//m_touch_collision_direction[1] = GameManager::CollisionDetermination2(
			//	touchpos[1] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			//	(*Iterator)->getPosition() + Vec2(GameManager::LAYRE_SIZE.x / 2, -GameManager::LAYRE_SIZE.y), GameManager::LAYRE_SIZE);
			//b = (*Iterator)->getPosition().x;


			////挟んだか
			//if (m_touch_collision_direction[0] == up || m_touch_collision_direction[1] == under || m_touch_collision_direction[0] == under || m_touch_collision_direction[1] == up
			//	||m_touch_collision_direction[0] == left || m_touch_collision_direction[1] == left || m_touch_collision_direction[0] == right || m_touch_collision_direction[1] == right)
			//{
				// 普通の画像から変更
				Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/needle2.png");
				(*Iterator)->setTexture(texture);
				needle[GameManager::PlayerMapPos]->m_needle_state[loop_cnt] = false;
		//	}

		}

		loop_cnt++;
	}

}

