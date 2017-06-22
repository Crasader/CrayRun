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
#include "../GameManager.h"

//ページ数
#define MAX_INFOMATION_PASE 7

class InfoScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(InfoScene);
	//初期化する
	bool init();


	//毎フレーム呼び出される関数
	void update(float delta)override;
private:
	cocos2d::ui::Button* b_Next;//ページを１ページ進めるボタン
	cocos2d::ui::Button* b_Back;//ページを１ページ戻すボタン
	cocos2d::ui::Button* b_BackScene;//タイトルに戻るためのボタン




	//ページを１ページ進めるボタンの座標
	const cocos2d::Vec2 NEXT_POS = cocos2d::Vec2(GameManager::SCREEN_SIZE.x - GameManager::SCREEN_SIZE.x / 5.0f, 100.0f);
	//ページを１ページ戻すボタンの座標
	const cocos2d::Vec2 BACK_POS = cocos2d::Vec2(GameManager::SCREEN_SIZE.x / 5.0f, 100.0f);
	//タイトルに戻るためのボタンの座標
	const cocos2d::Vec2 BACK_SCENE_POS = cocos2d::Vec2(GameManager::SCREEN_SIZE.x / 2.0f, 100.0f);


	//ボタンが押されたとき呼び出される関数
	void OnButtonTouchNext(cocos2d::Ref* ref,cocos2d::ui::Widget::TouchEventType eventtype);
	void OnButtonTouchBack(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventtype);



	cocos2d::Sprite* Infomation[MAX_INFOMATION_PASE];//説明画像
	int page;//ページ数
	int AnimationCnt;//アニメーション用カウント
	const int ANIMATION_FLAME = 10;

};