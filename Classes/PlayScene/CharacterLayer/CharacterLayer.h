/***************************************************************************
*|
*|	概要　　ResultLayer
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/

#pragma once 
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"
#include "Character.h"
#include "Rabbit.h"



//有効なタッチの数
static const int EFFECTIVENESS_TOUCH = 2;
class CharacterLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(CharacterLayer);



private:

	////毎フレーム呼び出される関数
	void update(float delta)override;
	//タッチ時に呼び出される
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//スワイプ時に呼び出される
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//タッチが離された
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);

	void onTouchesCancelled(const std::vector<cocos2d::Touch*>&touches, cocos2d::Event *unused_event);



	//プレイヤーとステージのあたり判定
	void AfterHittingFloor();
	//プレイヤーと斜面のあたり判定
	void AfterHittingSlope();
	//プレイヤーとギミックのあたり判定
	//void AfterHittingGimmick();
	//プレイヤーと金型のあたり判定
	//void AfterHittingMold();
	//スケール計算
	//void ScaleCalculation();
	//ジャンプするか調べる
	void JumpInvestigate();

	Character* character;

	//デバック用
	cocos2d::Label* n;
	int a = 19;

	

	//タッチID格納
	int m_touch_id;
	
	//タッチ座標
	cocos2d::Vec2 touchpos[EFFECTIVENESS_TOUCH];
	//タッチが当たった方向
	Direction m_touch_collision_direction[EFFECTIVENESS_TOUCH];

	//イテレータ
	cocos2d::Vector<cocos2d::Vec2>::iterator IteratorRight;
	cocos2d::Vector<cocos2d::Vec2>::iterator IteratorLeft;


	//タッチサイズ
	const cocos2d::Vec2 TOUCH_SIZE = cocos2d::Vec2(64, 64);
	
};

