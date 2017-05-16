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
	cocos2d::Sprite* s_Mold;//金型
	CharacterKind m_kind;//キャラクターの種類
	const cocos2d::Vec2 SIZE = cocos2d::Vec2(128, 128);

private:

};