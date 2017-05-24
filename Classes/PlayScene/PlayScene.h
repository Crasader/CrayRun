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
#include "../ResultScene/ResultScene.h"
#include "ui/CocosGUI.h"
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

	//3.2.1�̃X�v���C�g
	cocos2d::Sprite* Number[3];
	//�����̃A�N�V����
	void NumberAction(int cnt);
	//Go�̃X�v���C�g
	cocos2d::Sprite* Go;
	//�L�����N�^���C��
	CharacterLayer* characterlayer;
	//�J�����t���O
	bool m_CameraFlag;
	//�~�߂邩�ǂ���
	bool StopFlag;
	//���U���g�V�[����
	void TransitionPlayToResult() {
		cocos2d::Scene* nextScene = ResultScene::create(GameManager::Score, GameManager::TotalDistance);
		_director->replaceScene(nextScene);
	}
	//�G�t�F�N�g
	cocos2d::Sprite* Effect;

	//�X�e�[�W
	StageLayer* stagelayer;



};