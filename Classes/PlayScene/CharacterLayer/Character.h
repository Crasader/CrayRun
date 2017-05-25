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

	int walkCnt;//�������Ƃ��̃J�E���g

	void Move();//�ړ�
	void Jump();//�W�����v����
	virtual void Animation();

	//�d��
	void Gravity()
	{
		if (GameManager::RightFlag == false)
		{
			GameManager::PlayerSpd.x = 6.0f;
		}
		//�d�͉����x�ɏ����݂���
		if (GameManager::PlayerSpd.y >= -7.0f)
		{
			GameManager::PlayerSpd.y -= 0.6f;
		}

	}

	void setScale();//�T�C�Y�ݒ�
	//�v���C���[
	cocos2d::Sprite* s_player;
	//�v���C���[�̍ő�T�C�Y
	const int PLAYER_MAX_SIZE = 96;
	int i = 0;

	//���Ԗڂ̃}�b�v�ɂ��邩���߂�
	void GetLoopPos()
	{
		GameManager::PlayerMapPos = GameManager::PlayerPos.x / GameManager::MAP_SIZE.x;
		//if (GameManager::PlayerMapPos == i)
		//{
		//	int a = 0;
		//	i++;
		//}
	/*if (static_cast<int>(GameManager::PlayerPos.x) % static_cast<int>(GameManager::MAP_SIZE.x) != 0)
		{
			GameManager::PlayerMapPos++;
		}*/
	}


	//�L�����N�^��������
	void JumpBan() {
		if (GameManager::PlayerPos.y > GameManager::SCREEN_SIZE.y - GameManager::PlayerSize.y + 5	)
		{
			GameManager::PlayerSpd.y = 0; 
			GameManager::PlayerPos.y = GameManager::SCREEN_SIZE.y - GameManager::PlayerSize.y ;
		}
	}

	float JumpSize;//�W�����v���邨������
	

	int JumpCnt;//�W�����v�̃J�E���g
	bool JumpFlag;//�W�����v�ł��邩

	bool isScale;//���W�̑傫�����ύX����Ă��邩true�F����Ă���,false�F����Ă��Ȃ�


	bool FloormultipleFlag;//���̉��ɓ������Ă��邩
};

