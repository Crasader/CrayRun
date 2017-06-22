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


class NeedleSprite :public cocos2d::Sprite
{
public:
	//�V�[�����쐬����
	static NeedleSprite* create(std::string filename);

	//����������
	virtual bool init(std::string filename);
	//�傫��
	cocos2d::Vec2 m_size;
	//�}���`�^�b�`����
	void MultiTouchColliosion(cocos2d::Vec2 touchpos);
private:
	void  update(float data)override;//���t���[��
									 //�v���C���Ƃ̂����蔻��
	void CollisionPlayer();
	//�傫���̍ő�l
	const cocos2d::Vec2 MAX_SIZE = cocos2d::Vec2(120.0f,120.0f);
	//�j�̏��
	bool m_state;
};

