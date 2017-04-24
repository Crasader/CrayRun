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
	//�V�[�����쐬����
	//static cocos2d::Scene* createScene();
	CREATE_FUNC(PlayScene);
	//����������
	virtual bool init();

private:
	//���t���[���Ă΂��
	void update(float data)override;
	cocos2d::Camera* m_camera;
	float m_cameraposx;
	float m_cameraspdx;
};