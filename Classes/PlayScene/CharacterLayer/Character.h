/***************************************************************************
*|
*|	�T�v�@�@�L�����N�^�N���X�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
#pragma once
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "cocos2d.h"
#include "GameManager.h"

class Character :public cocos2d::Node
{
public:
	virtual bool init();
	CREATE_FUNC(Character);

	void Move();//�ړ�
	virtual void Jump();//�W�����v����
	//�d��
	void Gravity()
	{
		if (GameManager::RightFlag == false)
		{
			GameManager::PlayerSpd.x = 6.0f;
		}
		//�d�͉����x�ɏ����݂���
		if (GameManager::PlayerSpd.y >= -4.5f)
		{
			GameManager::PlayerSpd.y -= 0.4f;
		}
		//�W�����v���Ȃ��Ƃ��͊֌W�Ȃ������x������
		else if (JumpFlag == false)
		{
			GameManager::PlayerSpd.y -= 0.4f;
		}
	}

	void setScale();//�T�C�Y�ݒ�
	//�v���C���[
	cocos2d::Sprite* s_player;
	//�v���C���[�̍ő�T�C�Y
	const int PLAYER_MAX_SIZE = 64;

	bool JumpFlag;//�n�ʂɂ��Ă��邩
protected:
	int JumpCnt;//�W�����v�t���O

};

