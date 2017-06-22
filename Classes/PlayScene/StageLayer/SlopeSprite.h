/***************************************************************************
*|
*|	�T�v�@�@�j�X�v���C�g�N���X�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/6/5
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once
/* ----  �C���N���[�h ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"


class SlopeSprite :public cocos2d::Sprite
{
public:
	//�V�[�����쐬����
	static SlopeSprite* create(std::string filename, cocos2d::Vec2 Leftpos,cocos2d::Vec2 RightPos);

	//����������
	virtual bool init(std::string filename, cocos2d::Vec2 Leftpos, cocos2d::Vec2 RightPos);
	//�傫��
	cocos2d::Vec2 m_size;
	
private:
	void  update(float data)override;//���t���[��
									 //�v���C���Ƃ̂����蔻��
	void CollisionPlayer();
	
	cocos2d::Vec2 m_left_pos;//�����_�̍��W
	cocos2d::Vec2 m_right_pos;//�E���_�̍��W
	
};


