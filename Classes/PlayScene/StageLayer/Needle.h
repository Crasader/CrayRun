/***************************************************************************
*|
*|	概要　　針の宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- 多重インクルードの防止 ---------- */
#pragma once
/* ----  インクルード ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"

class Needle :public cocos2d::Node
{
public:
	bool init();
	CREATE_FUNC(Needle);
	//針スプライト
	std::vector<cocos2d::Sprite*> s_needle;
	//針状態
	std::vector<bool> m_needle_state;
	//サイズ
	const cocos2d::Vec2 SIZE = cocos2d::Vec2(100,100);
private:
	//イテレータ
	cocos2d::Vector<cocos2d::Sprite*>::iterator m_iterator_needle;
	//何個目かをカウントする
	int m_needle_cnt;
};
