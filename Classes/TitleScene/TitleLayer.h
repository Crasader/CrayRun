/// <summary>
/// タイトルのレイヤー
/// </summary>
#pragma once

#include<cocos2d.h>

class TitleLayer : public cocos2d::Layer
{
public:
	bool init();
	CREATE_FUNC(TitleLayer);


private:

	//毎フレーム呼び出される関数
	void update(float delta)override;

	//タッチ時に呼び出される
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//スワイプ時に呼び出される
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//タッチが離された
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//タッチ異常終了
	void onTouchesCancelled(const std::vector<cocos2d::Touch*>&touches, cocos2d::Event *unused_event);

	
};