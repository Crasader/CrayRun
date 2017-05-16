/***************************************************************************
*|
*|	概要　　ステージレイヤーの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/

#pragma once 
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "Coin.h"
#include "Mold.h"
#include "CrayStage.h"
#include "Stage.h"
#include "Slope.h"

class StageLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(StageLayer);


private:
	//スワイプ時に呼び出される
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);

	//毎フレーム呼び出される関数
	void update(float delta)override;
	//プレイヤーとコインの当たり判定後
	void CollisionResponseCoin();
	//プレイヤと金型のあたり判定
	void HittingMold();
	//金型と床のあたり判定
	void HittingFloorToMold();
	//ステージ生成
	void MapCreate();
	//ステージ削除
	void MapDelete();


	//金型オブジェクト
	std::vector<Mold*> mold;
	//床
	Stage* stage;
	//粘土床
	std::vector<CrayStage*> craystage;
	//コイン
	std::vector<Coin*> coin;
	//斜面
	std::vector<Slope*>slope;
	//マップイテレーター
	cocos2d::Vector<cocos2d::TMXTiledMap*>::iterator IteratorMap;
	//コインイテレータ
	cocos2d::Vector<Coin*>::iterator IteratorCoin;
	//斜面イテレーター
	cocos2d::Vector<Slope*>::iterator IteratorSlope;
	//粘土床イテレーター
	cocos2d::Vector<CrayStage*>::iterator ItratorCrayStage;

	//タッチサイズ
	const cocos2d::Vec2 TOUCH_SIZE = cocos2d::Vec2(60, 60);


	int m_data;
};


