/***************************************************************************
*|
*|	概要　　粘土床スプライトクラスの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- 多重インクルードの防止 ---------- */
#pragma once
/* ----  インクルード ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"
//有効なタッチの数
const int EFFECTIVENESSTOUCH = 2;

class CrayStageSprite :public cocos2d::Sprite
{
public:
	//シーンを作成する
	static CrayStageSprite* create(std::string filename);

	//初期化処理
	virtual bool init(std::string filename);
	//大きさ
	cocos2d::Vec2 m_size;

private:
	void  update(float data)override;//毎フレーム
	//プレイヤとのあたり判定
	void CollisionPlayer();
	//大きさの最大値
	const cocos2d::Vec2 MAX_SIZE = cocos2d::Vec2(192, 256);
	//スワイプ時に呼び出される
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//粘土床のマルチタッチ判定
	void MultiTouchCrayStage();
	//上下か左右どちらに小さくなるか求める
	void DirectionJudgment();
	//タッチ座標
	cocos2d::Vec2 touchpos[EFFECTIVENESSTOUCH];

	//タッチ座標
	cocos2d::Vec2 old_touchpos[EFFECTIVENESSTOUCH];

	//前フレームも二本の指が当たっているか確かめるためのフラグ
	bool hit_flag;

	//線形補間
	float Leap(float StartPosition, float GoalPosition, float Time)
	{
		return ((1 - Time) * StartPosition + GoalPosition * Time);
	}

	bool m_leap_flag;

	int m_flame_cnt;
	int m_time;

};
