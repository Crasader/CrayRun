/***************************************************************************
*|
*|	概要　　タイトルレイヤクラスを定義する
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/6/1
*|___________________________________________________________________________
****************************************************************************/
/* ---- 多重インクルードの防止 ---------- */
#pragma once

/* ---- インクルード ---------- */
#include<cocos2d.h>
#include<ui/CocosGUI.h>
#include "../PlayScene/PlayScene.h"

class TitleLayer : public cocos2d::Layer
{
public:
	bool init();
	CREATE_FUNC(TitleLayer)


private:

	//毎フレーム呼び出される関数
	void update(float delta)override;


	cocos2d::ui::Button* b_start;
	cocos2d::ui::Button* b_info;
	cocos2d::ui::Button* b_exit;
	int TitleBgm;

};