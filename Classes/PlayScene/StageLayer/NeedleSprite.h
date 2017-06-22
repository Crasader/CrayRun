/***************************************************************************
*|
*|	概要　　針スプライトクラスの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/6/5
*|___________________________________________________________________________
****************************************************************************/
/* ---- 多重インクルードの防止 ---------- */
#pragma once
/* ----  インクルード ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"


class NeedleSprite :public cocos2d::Sprite
{
public:
	//シーンを作成する
	static NeedleSprite* create(std::string filename);

	//初期化処理
	virtual bool init(std::string filename);
	//大きさ
	cocos2d::Vec2 m_size;
	//マルチタッチ判定
	void MultiTouchColliosion(cocos2d::Vec2 touchpos);
private:
	void  update(float data)override;//毎フレーム
									 //プレイヤとのあたり判定
	void CollisionPlayer();
	//大きさの最大値
	const cocos2d::Vec2 MAX_SIZE = cocos2d::Vec2(120.0f,120.0f);
	//針の状態
	bool m_state;
};

