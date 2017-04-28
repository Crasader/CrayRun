/***************************************************************************
*|
*|	概要　　リザルトレイヤー
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "StageLayer.h"
#include "../CharacterLayer/CharacterLayer.h"]
#include "Manager.h"

USING_NS_CC;

bool StageLayer::init()
{
	if (!Layer::init()) {

		return false;

	}

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

	this->scheduleUpdate();


	return true;

}


/***************************************************************************
*|	概要　　毎フレーム呼ばれる
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void StageLayer::update(float data) {
	AfterHittingCoin();


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
				GameManager::Score += GameManager::CoinPoint[i];
			}
		}
	}
};