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

	void Move();//�ړ�
	//virtual void Jump();//�W�����v����
	void Gravity();//�d��
	//void Configuration();//�ݒ�
private:
	cocos2d::Sprite* s_player;

	//�e�X�g�Ζ�
	cocos2d::Sprite* s_Sorp;
};

