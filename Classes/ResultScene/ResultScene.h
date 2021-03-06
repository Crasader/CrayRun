/***************************************************************************
*|
*|	概要　リザルトシーンの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ---- 多重インクルードの防止 ---------- */
#pragma once

/* ----  インクルード ---------- */
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../GameManager.h"
#include "ResultLayer.h"
class ResultScene :public cocos2d::Scene, public cocos2d::ui::EditBoxDelegate
{
public:
	//シーンを作成する
	static cocos2d::Scene* create(int score, int distance);
	//初期化する
	 bool init(int score,int distance);

private:
	//タッチされたら
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent);
	////毎フレーム呼ばれる
	//void update(float data)override;

	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)override;
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)override;
	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)override;
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox)override;
	//アップデート関数
	void update(float data)override;
	//リザルトレイヤオブジェクト
	ResultLayer* resultlayer;

	//らんきんぐネームの背景
	cocos2d::Sprite* InputNameBackGround;


	//左右のドーロ君
	cocos2d::Sprite* left_dorokun;
	cocos2d::Sprite* right_dorokun;
};