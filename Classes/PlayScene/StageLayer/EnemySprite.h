/***************************************************************************
*|
*|	�T�v�@�@�G�X�v���C�g�N���X�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/6/5
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once
/* ----  �C���N���[�h ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"


class EnemySprite :public cocos2d::Sprite
{
public:
	//�V�[�����쐬����
	static EnemySprite* create(std::string filename);

	//����������
	virtual bool init(std::string filename);
	
	
private:
	void  update(float data)override;//���t���[��
	const float ENEMY_SIZE = 4.0f;
	//�A�j���[�V�����p�̃J�E���g
	int m_animation_cnt;
	void Animation();//�A�j���[�V����������
	void CollisionPlayer();//�v���C���Ƃ̓����蔻��
};

