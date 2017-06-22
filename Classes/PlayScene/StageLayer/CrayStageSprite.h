/***************************************************************************
*|
*|	�T�v�@�@�S�y���X�v���C�g�N���X�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once
/* ----  �C���N���[�h ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"
//�L���ȃ^�b�`�̐�
const int EFFECTIVENESSTOUCH = 2;

class CrayStageSprite :public cocos2d::Sprite
{
public:
	//�V�[�����쐬����
	static CrayStageSprite* create(std::string filename);

	//����������
	virtual bool init(std::string filename);
	//�傫��
	cocos2d::Vec2 m_size;

private:
	void  update(float data)override;//���t���[��
	//�v���C���Ƃ̂����蔻��
	void CollisionPlayer();
	//�傫���̍ő�l
	const cocos2d::Vec2 MAX_SIZE = cocos2d::Vec2(192, 256);
	//�X���C�v���ɌĂяo�����
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//�S�y���̃}���`�^�b�`����
	void MultiTouchCrayStage();
	//�㉺�����E�ǂ���ɏ������Ȃ邩���߂�
	void DirectionJudgment();
	//�^�b�`���W
	cocos2d::Vec2 touchpos[EFFECTIVENESSTOUCH];

	//�^�b�`���W
	cocos2d::Vec2 old_touchpos[EFFECTIVENESSTOUCH];

	//�O�t���[������{�̎w���������Ă��邩�m���߂邽�߂̃t���O
	bool hit_flag;

	//���`���
	float Leap(float StartPosition, float GoalPosition, float Time)
	{
		return ((1 - Time) * StartPosition + GoalPosition * Time);
	}

	bool m_leap_flag;

	int m_flame_cnt;
	int m_time;

};
