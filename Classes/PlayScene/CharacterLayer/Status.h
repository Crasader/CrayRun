/// <summary>
/// �T�@�v�F�X�e�[�^�X�̒�`
/// �쐬�ҁFGS2 24 �R�{�I��
/// �쐬���F2017/05/15
/// </summary>
#pragma once
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "cocos2d.h"
#include "GameManager.h"

class Status : public cocos2d::Node
{
public:

	virtual bool init();
	
	CREATE_FUNC(Status);

	////���t���[���Ăяo�����֐�
	void update(float delta)override;

private:

	//�X�e�[�^�X�̃X�v���C�g
	cocos2d::Sprite* s_status;

	//�J�E���g
	int m_cnt;

	//�X�v���C�g���쐬����֐�
	void CreateSprite();
};