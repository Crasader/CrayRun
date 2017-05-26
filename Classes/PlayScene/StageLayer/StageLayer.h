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
#include "Needle.h"

//有効なタッチの数
const int EFFECTIVENESSTOUCH = 2;
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
	//プレイヤと針の当たり判定
	void HittingNeedle();
	//ステージ生成
	void MapCreate();
	//ステージ削除
	void MapDelete();
	//粘土床のマルチタッチ判定
	void  MultiTouchCrayStage();
	//針のマルチタッチ判定
	void  MultiTouchNeedle();

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
	//マップイテレーター
	cocos2d::Vector<cocos2d::TMXTiledMap*>::iterator IteratorMap;
	//コインイテレータ
	cocos2d::Vector<Coin*>::iterator IteratorCoin;
	//斜面イテレーター
	cocos2d::Vector<Slope*>::iterator IteratorSlope;
	//粘土床イテレーター
	cocos2d::Vector<CrayStage*>::iterator ItratorCrayStage;
	//針イテレーター
	cocos2d::Vector<Needle*> ::iterator ItratorNeedle;
	//金型イテレーター
	cocos2d::Vector<Mold*>::iterator ItratorMold;
	//タッチサイズ
	const cocos2d::Vec2 TOUCH_SIZE = cocos2d::Vec2(150, 150);
	const cocos2d::Vec2 TOUCH_SIZE2 = cocos2d::Vec2(30, 30);


	//タッチ座標
	cocos2d::Vec2 touchpos[EFFECTIVENESSTOUCH];
	//削除する場所
	int DeleteCnt;
	//デバック用
	cocos2d::Label* n;
	int a;
	int b;
	//マップの数
	const int MAX_MAP = 3;
	//前回のマップ
	int OldMap;
};


