/***************************************************************************
*|
*|	概要　　ステージレイヤー
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "StageLayer.h"
#include "../CharacterLayer/CharacterLayer.h"
#include "../../GameManager.h"
/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace std;
bool StageLayer::init()
{
	if (!Layer::init()) {

		return false;

	}
	log("############################### StageLayer created");

	/////////マップ描画////////

	//タイルマップの読み込み
	//マップチップ
	GameManager::map.push_back(TMXTiledMap::create("floor.tmx"));
	IteratorMap = GameManager::map.begin();
	TMXTiledMap* g_Map = *IteratorMap;
	//タイルマップの中心座標を設定
	g_Map->setAnchorPoint(Vec2(0, 0));
	//タイルマップの座標設定
	g_Map->setPosition(Point(0, 0));
	//画像の描画
	this->addChild(g_Map);
	//レイヤーにノードを集約
	CrayStage* craystage = CrayStage::create();
	this->addChild(craystage);
	//レイヤーにノードを集約
	stage = Stage::create();
	this->addChild(stage);
	//レイヤーにノードを集約
	coin.push_back(Coin::create());
	IteratorCoin = coin.begin();
	this->addChild(*IteratorCoin);
	//レイヤーにノードを集約
<<<<<<< HEAD
	slope = Slope::create();
	this->addChild(slope);

	////レイヤーにノードを集約
=======
	slope.push_back(Slope::create());
	IteratorSlope = slope.begin();
	this->addChild(*IteratorSlope);
	//レイヤーにノードを集約
>>>>>>> eb5b5cb02019439b4b6297fa3b3ec5d79ce0de9c
	Rmold = RabbitMold::create();
	this->addChild(Rmold);

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
	
	Vector<Vec2>::iterator Iterator;

	int i = 0;
	//床の数だけループ
	for (Iterator = GameManager::MoldPos.begin(); Iterator != GameManager::MoldPos.end(); ++Iterator)
	{
		Node* q = Rmold->getChildByTag(i);
		Vec2 vec = *Iterator;
		vec += GameManager::MoldSpd;
		q->setPosition(vec);
		i++;
	}

	//コインあたり判定
	CollisionResponseCoin();
	HittingMold();
	HittingFloorToMold();

	if (static_cast<int>(GameManager::m_cameraposx + 480 ) % static_cast<int>(GameManager::MAP_SIZE.x) == 0)
	{
<<<<<<< HEAD
		GameManager::StageLoopCnt++;
		//GameManager::AllFloorPos.push_back(GameManager::StageLoopCnt);
		//タイルマップの読み込み
		//マップチップ
		GameManager::map = TMXTiledMap::create("floor.tmx");
		//タイルマップの中心座標を設定
		GameManager::map->setAnchorPoint(Vec2(0, 0));
		//タイルマップの座標設定
		GameManager::map->setPosition(Point(GameManager::m_cameraposx + 480, 0));
		//画像の描画
		this->addChild(GameManager::map);

		//ステージ座標を取得
		stage->init();

		//vectorにコインオブジェクトのアドレスを格納する
		coin.push_back(Coin::create());
		//イテレータにコインの最初の要素を格納する
		IteratorCoin = coin.begin();
		//ループさせたステージの数を見る
		IteratorCoin += GameManager::StageLoopCnt;
		this->addChild(*IteratorCoin);

		//斜面座標を取得
		slope->init();
=======
		//マップ生成
		MapCreate();
		if (GameManager::MapLoopCnt > 2)
		{
			//マップ削除
			MapDelete();
		}
>>>>>>> eb5b5cb02019439b4b6297fa3b3ec5d79ce0de9c

	}
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

	//ステージ座標を取得
	stage->init();

	//vectorにコインオブジェクトのアドレスを格納する
	coin.push_back(Coin::create());
	//イテレータにコインの最初の要素を格納する
	IteratorCoin = coin.begin();
	//ループさせたステージの数を見る
	IteratorCoin += GameManager::MapLoopCnt;
	this->addChild(*IteratorCoin);


	//斜面座標を取得
	slope.push_back(Slope::create());
	IteratorSlope = slope.begin();
	IteratorSlope += GameManager::MapLoopCnt;
	this->addChild(*IteratorSlope);
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

	//斜面座標の削除
	GameManager::AllLeftPos[GameManager::MapLoopCnt - 2].crend();
	GameManager::AllRightPos[GameManager::MapLoopCnt - 2].crend();
	//コイン削除
	coin[GameManager::MapLoopCnt - 2]->removeFromParent();
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
			Node* n_coin = m_SaveCoin->getChildByTag(g_LoopCnt);
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
	//}
}


//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//	概　要：金型あたり判定
//	引　数：無し
//　戻り値：無し
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
void StageLayer::HittingMold()
{
	for (int i = 0; i < GameManager::MoldCnt; i++)
	{
		Node* q = Rmold->getChildByTag(i);
		if (q != nullptr)
		{
			//金型
			if (GameManager::HitJudgment
			(q->getPosition(), q->getContentSize(),
				GameManager::PlayerPos, GameManager::PlayerSize) == true)
			{
				//当たった金型を削除
				Rmold->getChildByTag(i)->removeFromParent();
				//兎型のキャラクターに変更
				GameManager::Mold = 1;
				GameManager::ChangeMold = true;
			}
		}
	}
};

/***************************************************************************
*|	概要　	金型と床の衝突判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void StageLayer::HittingFloorToMold()
{

	//std::vector<Vec2>::iterator Iterator;

	////マップの数だけループ
	//for (int j = 0; j <= GameManager::MapLoopCnt; j++)
	//{
	//	//床の数だけループ
	//	for (Iterator = GameManager::AllFloorPos[j].begin(); Iterator != GameManager::AllFloorPos[j].end(); ++Iterator)
	//	{
	//		for (int i = 0; i < GameManager::MoldCnt; i++)
	//		{
	//			Node* q = Rmold->getChildByTag(i);
	//			if (q != nullptr) {
	//				Vec2 vec = *Iterator;
	//				switch (GameManager::CollisionDetermination
	//				(vec, GameManager::LAYRE_SIZE,
	//					q->getPosition(), q->getContentSize())
	//					)
	//				{
	//				case up:
	//					q->setPositionY(vec.y);
	//					GameManager::MoldSpd.y = 0.0f;
	//				}
	//			}
	//		}
	//	}
	//}
}

