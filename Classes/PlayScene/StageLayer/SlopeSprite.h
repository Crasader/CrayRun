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


class SlopeSprite :public cocos2d::Sprite
{
public:
	//シーンを作成する
	static SlopeSprite* create(std::string filename, cocos2d::Vec2 Leftpos,cocos2d::Vec2 RightPos);

	//初期化処理
	virtual bool init(std::string filename, cocos2d::Vec2 Leftpos, cocos2d::Vec2 RightPos);
	//大きさ
	cocos2d::Vec2 m_size;
	
private:
	void  update(float data)override;//毎フレーム
									 //プレイヤとのあたり判定
	void CollisionPlayer();
	
	cocos2d::Vec2 m_left_pos;//左頂点の座標
	cocos2d::Vec2 m_right_pos;//右頂点の座標
	
};


