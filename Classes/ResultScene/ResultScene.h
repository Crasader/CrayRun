#pragma once

/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "../GameManager.h"

class ResultScene :public cocos2d::Scene
{
public:
	//シーンを作成する
	static cocos2d::Scene* create(int score);
	//初期化する
	 bool init(int score);

private:
	////毎フレーム呼ばれる
	//void update(float data)override;

};