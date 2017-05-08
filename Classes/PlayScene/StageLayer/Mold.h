//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//
//　ファイル名：RabbitMold.h
//
//	概　　　要：兎型の金型
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
	cocos2d::Sprite* s_Mold;//コイン



	//重力
	void Gravity()
	{
		if (GameManager::RightFlag == false)
		{
			GameManager::MoldSpd.x = 6.0f;
		}
		//重力加速度に上限を設ける
		if (GameManager::MoldSpd.y >= -4.5f)
		{
			GameManager::MoldSpd.y -= 0.4f;
		}
		//ジャンプがないときは関係なく加速度をつける
		else
		{
			GameManager::MoldSpd.y -= 0.4f;
		}
	}


private:

};