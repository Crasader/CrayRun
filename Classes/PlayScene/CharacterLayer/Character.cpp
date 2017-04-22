/***************************************************************************
*|
*|	�T�v�@�X�R�A�N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "Character.h"


USING_NS_CC;
using namespace cocos2d::experimental;



bool Character::init()
{
	if (!Node::init()) {

		return false;
	}

	//�v���C���[�쐬
	s_player = Sprite::create("Images/1.png");
	s_player->setPosition(GameManager::PlayerPos);
	s_player->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(s_player);





	return true;
}

/***************************************************************************
*|	�T�v�@�@�ړ�����
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void Character::Move()
{
	//���W�ɑ��x������
	GameManager::PlayerPos += GameManager::PlayerSpd;
	//���W��K�p������
	s_player->setPosition(GameManager::PlayerPos);
}

/***************************************************************************
*|	�T�v�@  �W�����v
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void Character::Jump()
{
	JumpBy* jumpaction = JumpBy::create(0.5f, Vec2(0,0), 64.0f, 1);
	this->runAction(jumpaction);

}


/***************************************************************************
*|	�T�v�@�@�d��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void Character::Gravity()
{
	if (GameManager::SlopeFalg == true)
	{
		GameManager::PlayerSpd.y = 0.0f;
	}
	else
	{
		GameManager::PlayerSpd.y = -4.0f;
	}
}


