/***************************************************************************
*|
*|	概要　　敵スプライトクラスの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/6/5
*|___________________________________________________________________________
****************************************************************************/
/* ---- 多重インクルードの防止 ---------- */
#pragma once
/* ----  インクルード ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"


class EnemySprite :public cocos2d::Sprite
{
public:
	//シーンを作成する
	static EnemySprite* create(std::string filename);

	//初期化処理
	virtual bool init(std::string filename);
	
	
private:
	void  update(float data)override;//毎フレーム
	const float ENEMY_SIZE = 4.0f;
	//アニメーション用のカウント
	int m_animation_cnt;
	void Animation();//アニメーションさせる
	void CollisionPlayer();//プレイヤとの当たり判定
};

