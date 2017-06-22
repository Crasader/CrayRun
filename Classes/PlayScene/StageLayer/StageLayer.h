/***************************************************************************
*|
*|	概要　　ステージレイヤーの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- 多重インクルードの防止 ---------- */
#pragma once 
/* ----  インクルード ---------- */
#include "cocos2d.h"
#include "Coin.h"
#include "Mold.h"
#include "CrayStage.h"
#include "Stage.h"
#include "Slope.h"
#include "Needle.h"
#include "Enemy.h"

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
	//プレイヤと金型のあたり判定
	void HittingMold();
	//ステージ生成
	void MapCreate();
	//ステージ削除
	void MapDelete();


	cocos2d::Sprite* background;

	//針
	std::vector<Needle*> needle;
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
	//敵
	std::vector<Enemy*> enemy;

	//マップの数
	const int MAX_MAP = 3;
	//前回のマップ
	int OldMap;
	//金型パーティクル
	void MoldParticle(cocos2d::Vec2 Position);
};


