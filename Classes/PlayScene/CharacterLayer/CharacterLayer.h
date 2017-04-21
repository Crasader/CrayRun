/***************************************************************************
*|
*|	�T�v�@�@ResultLayer
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/

#pragma once 
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "cocos2d.h"
#include "GameManager.h"
#include "Character.h"
#include "Rabbit.h"

class CharacterLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(CharacterLayer);


private:
	//�L�����N�^�[
	Character* character;
	////���t���[���Ăяo�����֐�
	void update(float delta)override;

	//�v���C���[�ƃX�e�[�W�̂����蔻��
	//void AfterHittingStage();
	//�v���C���[�ƎΖʂ̂����蔻��
	void AfterHittingSlope();
	//�v���C���[�ƃM�~�b�N�̂����蔻��
	//void AfterHittingGimmick();
	//�v���C���[�Ƌ��^�̂����蔻��
	//void AfterHittingMold();
	//�X�P�[���v�Z
	//void ScaleCalculation();

};

