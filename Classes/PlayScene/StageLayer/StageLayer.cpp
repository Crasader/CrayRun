/***************************************************************************
*|
*|	概要　　ステージレイヤーの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "../../GameManager.h"
#include "StageLayer.h"
#include "audio/include/AudioEngine.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;


//using namespace std;
/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool StageLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	////マップ生成
	//MapCreate();
	



	// Register Touch Event
	EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(StageLayer::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(StageLayer::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(StageLayer::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(StageLayer::onTouchesCancelled, this);

	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//_touchListener = listener;

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
			
			//マップ生成
			MapCreate();
			//////床
			stage = Stage::create();
			this->addChild(stage);
	
			if (GameManager::MapLoopCnt > 1)
			{
				//ステージ削除
				MapDelete();
			}
			GameManager::MapLoopCnt++;
	}
	//金型当たり判定
	HittingMold();
	////コインの音がtrueの時は回す
	//if (coin_Audio_flag == false)
	//{
	//	coin_cnt++;
	//}
	//if (coin_cnt > 60)
	//{
	//	coin_Audio_flag = true;
	//	coin_cnt = 0;
	//}

	
}

/***************************************************************************
*|	概要　  ステージ生成
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void StageLayer::MapCreate()
{

	//タイルマップの読み込み
	int NowMap = rand() % MAX_MAP + 1;
	//前回とは違うマップになるようにループする
	while (OldMap == NowMap)
	{
		NowMap = rand() % MAX_MAP + 1;
	}


	//前回のマップを更新する
	OldMap = NowMap;
	std::ostringstream MapName;

	//二週目までは簡単なステージを作成する
	if (GameManager::MapLoopCnt == 0)
	{
		MapName << "Map/EasyMap" << NowMap << ".tmx";
		//マップチップ
		GameManager::map.push_back(TMXTiledMap::create(MapName.str()));
		//GameManager::map.push_back(TMXTiledMap::create("Map/NewMap1.tmx"));
	}
	else
	{
		MapName << "Map/NewMap" << NowMap << ".tmx";
		//マップチップ
		GameManager::map.push_back(TMXTiledMap::create(MapName.str()));
		//GameManager::map.push_back(TMXTiledMap::create("Map/NewMap2.tmx"));
	}
	
//	TMXTiledMap* g_Map = *IteratorMap;
	//タイルマップの中心座標を設定
	GameManager::map[GameManager::MapLoopCnt]->setAnchorPoint(Vec2(0, 0));
	//タイルマップの座標設定
	GameManager::map[GameManager::MapLoopCnt]->setPosition(Point(GameManager::MAP_SIZE.x * GameManager::MapLoopCnt, 0));
	//画像の描画
	this->addChild(GameManager::map[GameManager::MapLoopCnt]);


	//粘土床
	craystage.push_back(CrayStage::create());
	this->addChild(craystage[GameManager::MapLoopCnt]);

	

	//斜面座標を取得
	slope.push_back(Slope::create());
	this->addChild(slope[GameManager::MapLoopCnt]);

	//金型作成
	mold.push_back(Mold::create());
	this->addChild(mold[GameManager::MapLoopCnt]);

	//針
	needle.push_back(Needle::create());
	this->addChild(needle[GameManager::MapLoopCnt]);

	//敵
	enemy.push_back(Enemy::create());
	this->addChild(enemy[GameManager::MapLoopCnt]);

	//コイン
	coin.push_back(Coin::create());
	this->addChild(coin[GameManager::MapLoopCnt], -100);
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

	GameManager::map[GameManager::MapLoopCnt - 2]->removeFromParent();


	//ステージの削除
	//std::remove(GameManager::AllFloorPos,DeleteCnt);
	//斜面ノードの削除
	slope[GameManager::MapLoopCnt- 2]->removeFromParent();

	//粘土床の削除
	craystage[GameManager::MapLoopCnt - 2]->removeFromParent();

	//金型削除
	mold[GameManager::MapLoopCnt - 2]->removeFromParent();
	//coin[GameManager::MapLoopCnt - 2]->removeFromParent();

	//針削除
	needle[GameManager::MapLoopCnt - 2]->removeFromParent();

	//敵削除
	enemy[GameManager::MapLoopCnt - 2]->removeFromParent();
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
			((*IteratorMold)->getPosition() , mold[GameManager::PlayerMapPos]->SIZE,
				GameManager::PlayerPos + Vec2(GameManager::PlayerSize.x / 2, GameManager::PlayerSize.y / 2), GameManager::PlayerSize) == true)
			{
				//当たった金型を削除
				//(*IteratorMold)->removeFromParent();
				
				//兎型のキャラクターに変更
				GameManager::Mold = mold[GameManager::PlayerMapPos]->m_kind[loop_cnt];
				GameManager::ChangeMold = true;
				//金型アクション
				//アクションを止める
				//(*IteratorMold)->stopAllActions();
				//mold[GameManager::PlayerMapPos]->s_BackMold[loop_cnt]->stopAllActions();

				//挟むアクション
				MoveBy* action1 = MoveBy::create(0.01f, Vec2(12, 0));
				(*IteratorMold)->runAction(action1);
				(*IteratorMold)->setScale(1.4f, 1.4f);

				MoveBy* action2 = MoveBy::create(0.01f, Vec2(-13.0f, 0.0f));
				CallFunc* action3 = CallFunc::create(CC_CALLBACK_0(StageLayer::MoldParticle, this, (*IteratorMold)->getPosition()- Vec2(70, 0)));
				Sequence* action4 = Sequence::create(action2, action3, nullptr);

				mold[GameManager::PlayerMapPos]->s_BackMold[loop_cnt]->runAction(action4);
				mold[GameManager::PlayerMapPos]->s_BackMold[loop_cnt]->setScale(1.4f, 1.4f);


				//金型パーティクル
				//StageLayer::MoldParticle((*IteratorMold)->getPosition() + Vec2(12, 0));

				(*IteratorMold) = nullptr;

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
	//有効なタッチの数
	const int EFFECTIVENESSTOUCH = 2;
	//タッチ座標
	cocos2d::Vec2 touchpos[EFFECTIVENESSTOUCH];


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
		std::vector<NeedleSprite*>::iterator needle_iterator;
		for (needle_iterator = needle[GameManager::PlayerMapPos]->m_needleSprite.begin();
			needle_iterator !=  needle[GameManager::PlayerMapPos]->m_needleSprite.end();
			needle_iterator++)
		{
			(*needle_iterator)->MultiTouchColliosion(*touchpos);
		}
		

		//初期化する
		touchpos[0] = Vec2(0.0f, 0.0f);
		touchpos[1] = Vec2(0.0f, 0.0f);
	}


}




//金型パーティクル
void StageLayer::MoldParticle(cocos2d::Vec2 Position)
{

	// 作成したパーティクルのプロパティリストを読み込み
	ParticleSystemQuad* particle = ParticleSystemQuad::create("Particle/particle_texture2.plist");
	//パーティクルのメモリーリーク回避（★重要）
	particle->setAutoRemoveOnFinish(true);
	// パーティクルを開始
	particle->resetSystem();
	// パーティクルを表示する場所の設定
	particle->setPosition(Position);
	//パーティクルのスケール
	particle->setScale(0.5);
	// パーティクルを配置
	this->addChild(particle);

	////パーティクルのアクション
	DelayTime* action = DelayTime::create(1.0f);
	RemoveSelf* action2 = RemoveSelf::create();
	Sequence* action3 = Sequence::create(action,action2,nullptr);
	particle->runAction(action3);

	experimental::AudioEngine::play2d("Sounds/mold.mp3");
	
}

