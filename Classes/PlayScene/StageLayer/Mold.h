//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//
//　ファイル名：Mold.h
//
//	概　　　要：金型
//
//　作　成　者：GS2 24 山本悠雅
//
//　作　成　日：2017/05/02
//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
//ライブラリのインクルード/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "cocos2d.h"
#include "GameManager.h"

class Mold : public cocos2d::Node {

public:
	virtual bool init();

	CREATE_FUNC(Mold);
	std::vector<cocos2d::Sprite*> s_Mold;//金型
	std::vector<cocos2d::Sprite*> s_BackMold;//奥の金型
	std::vector<CharacterKind> m_kind;//キャラクターの種類
	const cocos2d::Vec2 SIZE = cocos2d::Vec2(64 * 2.0f, 64 * 1.8f);

private:
	const int m_while_distance = 25;
};