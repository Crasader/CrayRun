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

bool StageLayer::init()
{
	if (!Layer::init()) {

		return false;

	}
	log("############################### StageLayer created");

	/////////マップ描画////////

	//タイルマップの読み込み
	//マップチップ
	GameManager::map = TMXTiledMap::create("floor.tmx");
	//タイルマップの中心座標を設定
	GameManager::map->setAnchorPoint(Vec2(0, 0));
	//タイルマップの座標設定
	GameManager::map->setPosition(Point(0, 0));
	//画像の描画
	this->addChild(GameManager::map);

	//レイヤーにノードを集約
	CrayStage* craystage = CrayStage::create();
	this->addChild(craystage);


	//レイヤーにノードを集約
	Stage* stage = Stage::create();
	this->addChild(stage);

	//レイヤーにノードを集約
	coin = Coin::create();
	this->addChild(coin);

	//レイヤーにノードを集約
	Slope* slope = Slope::create();
	this->addChild(slope);

	//レイヤーにノードを集約
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
	Rmold->Gravity();
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


	AfterHittingCoin();
	AfterHittingMold();
	AfterHittingFloorToMold();

	if (static_cast<int>(GameManager::m_cameraposx + 480 ) % static_cast<int>(GameManager::MAP_SIZE.x) == 0)
	{
		GameManager::StageLoopCnt++;
		//GameManager::FloorPos.push_back(GameManager::StageLoopCnt);
		//タイルマップの読み込み
		//マップチップ
		GameManager::map = TMXTiledMap::create("floor.tmx");
		//タイルマップの中心座標を設定
		GameManager::map->setAnchorPoint(Vec2(0, 0));
		//タイルマップの座標設定
		GameManager::map->setPosition(Point(GameManager::m_cameraposx + 480, 0));
		//画像の描画
		this->addChild(GameManager::map);
		////レイヤーにノードを集約
		Stage* stage = Stage::create();
		this->addChild(stage);
	}


}

/***************************************************************************
*|	概要　　コインあたり判定後
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void StageLayer::AfterHittingCoin()
{
	for (int i = 0; i < GameManager::CoinCnt; i++)
	{
		Node* q = coin->getChildByTag(i);
		if (q != nullptr)
		{
			//プレイヤーのコイン
			if (GameManager::HitJudgment
			(q->getPosition(), q->getContentSize(),
				GameManager::PlayerPos, GameManager::PlayerSize) == true)
			{
				//当たったコインを削除
				coin->getChildByTag(i)->removeFromParent();
				//スコアにとったコインのポイントをたす
				GameManager::Score += GameManager::CoinPoint[i] * GameManager::ScoreCorrection;
			}
		}
	}
};

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//	概　要：金型あたり判定後
//	引　数：無し
//　戻り値：無し
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
void StageLayer::AfterHittingMold()
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
void StageLayer::AfterHittingFloorToMold()
{

	std::vector<Vec2>::iterator Iterator;

	//マップの数だけループ
	for (int j = 0; j <= GameManager::StageLoopCnt; j++)
	{
		//床の数だけループ
		for (Iterator = GameManager::FloorPos[j].begin(); Iterator != GameManager::FloorPos[j].end(); ++Iterator)
		{
			for (int i = 0; i < GameManager::MoldCnt; i++)
			{
				Node* q = Rmold->getChildByTag(i);
				if (q != nullptr) {
					Vec2 vec = *Iterator;
					switch (GameManager::CollisionDetermination
					(vec, GameManager::LAYRE_SIZE,
						q->getPosition(), q->getContentSize())
						)
					{
					case up:
						q->setPositionY(vec.y);
						GameManager::MoldSpd.y = 0.0f;
					}
				}
			}
		}
	}
}