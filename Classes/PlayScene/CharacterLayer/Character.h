/***************************************************************************
*|
*|	�T�v�@�@�X�R�A�N���X�̐錾
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

	//static Character* create();

	void Move();//�ړ�
	virtual void Jump();//�W�����v����
	//�d��
	void Character::Gravity()
	{
		if (GameManager::RightFlag == false)
		{
			GameManager::PlayerSpd.x = 6.0f;
		}
		GameManager::PlayerSpd.y -= 0.4f;
	}
	//void Configuration();//�ݒ�
	cocos2d::Sprite* s_player;
	//���W���擾����
	void GetPos() {
		GameManager::PlayerPos = s_player->getPosition();
	}
private:
	int F;
	float y_prev;
};

