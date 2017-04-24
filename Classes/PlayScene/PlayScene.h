#pragma once


#include "cocos2d.h"
#include "StageLayer\StageLayer.h"
#include "BackgroundLayer\BackgroundLayer.h"
#include "CharacterLayer\CharacterLayer.h"
#include "UILayer\UILayer.h"
#include "GameManager.h"


class PlayScene :public cocos2d::Scene
{
public:
	//シーンを作成する
	//static cocos2d::Scene* createScene();
	CREATE_FUNC(PlayScene);
	//初期化する
	virtual bool init();

private:
	//毎フレーム呼ばれる
	void update(float data)override;
	cocos2d::Camera* m_camera;
	float m_cameraposx;
	float m_cameraspdx;
};