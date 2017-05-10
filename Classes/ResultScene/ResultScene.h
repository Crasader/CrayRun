#pragma once

/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "../GameManager.h"

class ResultScene :public cocos2d::Scene
{
public:
	//シーンを作成する
	//static cocos2d::Scene* createScene();

	CREATE_FUNC(ResultScene);
	//初期化する
	virtual bool init();

private:
	//毎フレーム呼ばれる
	void update(float data)override;

};