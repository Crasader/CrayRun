/***************************************************************************
*|
*|	�T�v�@�@�X�e�[�^�X�N���X��錾����
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/6/1
*|___________________________________________________________________________
****************************************************************************/

/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once
/* ----  �C���N���[�h ---------- */
#include "cocos2d.h"
#include "GameManager.h"

class Status : public cocos2d::Node
{
public:

	virtual bool init();

	CREATE_FUNC(Status);

	////���t���[���Ăяo�����֐�
	void update(float delta)override;

	//�X�v���C�g���쐬����֐�
	void StatusAction();
private:

	//�X�e�[�^�X�̃X�v���C�g
	cocos2d::Sprite* s_status[GameManager::MaxCharacterKind];


};