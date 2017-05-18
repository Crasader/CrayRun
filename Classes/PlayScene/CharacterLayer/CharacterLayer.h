/***************************************************************************
*|
*|	概要　　キャラクターレイヤーの宣言
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
#include "Slime.h"
#include "Gnome.h"
#include "Phoenix.h"

#include "Status.h"



//有効なタッチの数
static const int EFFECTIVENESS_TOUCH = 2;
class CharacterLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(CharacterLayer);



private:


	//毎フレーム呼び出される関数
	void update(float delta)override;
	//タッチ時に呼び出される
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//スワイプ時に呼び出される
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//タッチが離された
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//タッチ異常終了
	void onTouchesCancelled(const std::vector<cocos2d::Touch*>&touches, cocos2d::Event *unused_event);

	//キャラクターのマルチタッチ判定
	void  MultiTouchCharacter();


	//金型の変更
	void ChangeMold();
	//プレイヤーとステージのあたり判定
	void CollisionResponseFloor();
	//プレイヤーと粘土床のあたり判定
	void CollisionResponseCrayFloor();
	//プレイヤーと斜面のあたり判定
	void  CollisionResponseSlope();
	//プレイヤーとギミックのあたり判定
	//void AfterHittingGimmick();

	//ジャンプするか調べる
	void JumpInvestigate();
	//キャラクターオブジェクト
	Character* character;

	Status* status;

	//デバック用
	cocos2d::Label* n;
	int a = 19;
	int b = 0;
	

	//タッチID格納
	int m_touch_id;
	
	//タッチ座標
	cocos2d::Vec2 touchpos[EFFECTIVENESS_TOUCH];
	//イテレータ
	cocos2d::Vector<cocos2d::Vec2>::iterator IteratorRight;
	cocos2d::Vector<cocos2d::Vec2>::iterator IteratorLeft;


	//タッチサイズ
	const cocos2d::Vec2 TOUCH_SIZE = cocos2d::Vec2(60,60);
	int FirstTouchCnt;//最初のタッチからどれだけ経過したか
	bool FirstTouchFlag = false;//最初のタッチが呼ばれたか

};

