/***************************************************************************
*|
*|	概要　　タイトルシーンクラスを定義する
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/6/1
*|___________________________________________________________________________
****************************************************************************/

/* ---- 多重インクルードの防止 ---------- */
#pragma once

/* ---- インクルード ---------- */
#include <cocos2d.h>

class TitleScene : public cocos2d::Scene {
public:
	//シーンを作成する
	static cocos2d::Scene* create();
	//初期化する
	bool init();

private:
	//タッチされたら
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent);


};