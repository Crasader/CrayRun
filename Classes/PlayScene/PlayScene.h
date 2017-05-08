/***************************************************************************
*|
*|	�T�v�@�@�v���C�V�[���N���X�̐錾
*|�@�쐬�ҁ@GF3 17 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
#pragma once

/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "cocos2d.h"
#include "StageLayer/StageLayer.h"
#include "BackgroundLayer/BackgroundLayer.h"
#include "CharacterLayer/CharacterLayer.h"
#include "UILayer/UILayer.h"
#include "../GameManager.h"


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
	cocos2d::Layer* uilayer;

};