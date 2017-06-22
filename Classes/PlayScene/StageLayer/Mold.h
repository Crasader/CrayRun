/***************************************************************************
*|
*|	概要　　金型クラスを定義する
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/6/1
*|___________________________________________________________________________
****************************************************************************/
/* ---- 多重インクルードの防止 ---------- */
#pragma once
/* ----  インクルード ---------- */
#include "cocos2d.h"
#include "GameManager.h"

class Mold : public cocos2d::Node {

public:
	virtual bool init();

	CREATE_FUNC(Mold);
	std::vector<cocos2d::Sprite*> s_Mold;//金型
	std::vector<cocos2d::Sprite*> s_BackMold;//奥の金型
	std::vector<GameManager::CharacterKind> m_kind;//キャラクターの種類
	const cocos2d::Vec2 SIZE = cocos2d::Vec2(64 * 1.6f, 64 * 1.4f);

private:
	const int m_while_distance = 25;
};