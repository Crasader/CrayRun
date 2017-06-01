/***************************************************************************
*|
*|	概要　　説明書クラスを定義する
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/6/1
*|___________________________________________________________________________
****************************************************************************/

/* ---- 多重インクルードの防止 ---------- */
#pragma once

/* ----  インクルード ---------- */
#include <cocos2d.h>
#include <ui/CocosGUI.h>

#define MAX_INFOMATION_PASE 6

class InfoScene : public cocos2d::Scene
{
public:
	//シーンを作成する
	static cocos2d::Scene* create();
	//初期化する
	bool init();


	//毎フレーム呼び出される関数
	void update(float delta)override;
private:
	cocos2d::ui::Button* b_Next;//ページを１ページ進める
	cocos2d::ui::Button* b_Back;//ページを１ページ戻す
	cocos2d::ui::Button* b_BackScene;//タイトルに戻るためのボタン

	void OnButtonTouchNext(cocos2d::Ref* ref,cocos2d::ui::Widget::TouchEventType eventtype);
	void OnButtonTouchBack(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventtype);



	cocos2d::Sprite* Infomation[MAX_INFOMATION_PASE];//説明画像
	int page;//ページ数
	int pageCnt;
};