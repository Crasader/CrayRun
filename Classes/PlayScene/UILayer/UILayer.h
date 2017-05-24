/***************************************************************************
*|
*|	概要　　UIレイヤーの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/

#pragma once 
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "Distance.h"
#include "Score.h"
#include "../../GameManager.h"
#include "ui/CocosGUI.h"
#include "Status.h"
#include  "Status.h"

class UiLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(UiLayer);


private:

	////毎フレーム呼び出される関数
	void update(float delta)override;
	Score* score;//スコア
	Distance * distance;//距離
	float m_distanceSpd;//	距離に足す値
	cocos2d::ui::Button* button;//ボタン

	void onButtonTouch(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType);
	int b;
	//デバック用
	cocos2d::Label* n;

	bool PauseFlag;

	//ステータス
	Status* status;


	float spd;
};


