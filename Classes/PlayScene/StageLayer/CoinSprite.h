/***************************************************************************
*|
*|	概要　　コインクラスの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- 多重インクルードの防止 ---------- */
#pragma once
/* ----  インクルード ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"


class CoinSprite :public cocos2d::Sprite
{
public:
	//シーンを作成する
	static CoinSprite* create(std::string filename, int point);

	//初期化処理
	virtual bool init(std::string filename, int point);


private:
	//魔法使いに吸収されるコインか判定する
	void CollisionAbsorptionCoin();
	//魔法使いに吸収するコインを線形補間で動かす
	void AbsorptionCoin();
	//コインのあたり判定
	void CollisionResponseCoin();
	//ステージレイヤが動き始めてからのフレーム数
	int FlameCnt;
	int m_CoinCnt;//コインをカウント
	bool m_absorption_flag;//魔法使いに吸収されるか
	int FlameTime;//線形補間が開始したとき
	int SEdis;//キャラクタとの距離
	void update(float data)override;//毎フレーム
	//吸収するサイズ
	const cocos2d::Vec2 AbsorptionSize = cocos2d::Vec2(400.0f, 400.0f);
	cocos2d::Vec2 m_startpos;//線形補間開始時のスタートの座標
	cocos2d::Vec2 m_endpos;//目標のの座標
	float AbsorptionPos = 13.0;
	bool m_Move_Flag;//移動するか
	int m_point;//スコアに入るポイント
	//線形補間
	cocos2d::Vec2 Leap(cocos2d::Vec2 StartPosition, cocos2d::Vec2 GoalPosition, float Time);

	

};

