/// <summary>
/// タイトルシーン
/// </summary>
#pragma once

#include <cocos2d.h>

class TitleScene : public cocos2d::Scene {
public:
	//シーンを作成する
	static cocos2d::Scene* create();
	//初期化する
	bool init();

private:
	//タッチされたら
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent);


};