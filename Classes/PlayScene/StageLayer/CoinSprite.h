/***************************************************************************
*|
*|	�T�v�@�@�R�C���N���X�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once
/* ----  �C���N���[�h ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"


class CoinSprite :public cocos2d::Sprite
{
public:
	//�V�[�����쐬����
	static CoinSprite* create(std::string filename, int point);

	//����������
	virtual bool init(std::string filename, int point);


private:
	//���@�g���ɋz�������R�C�������肷��
	void CollisionAbsorptionCoin();
	//���@�g���ɋz������R�C������`��Ԃœ�����
	void AbsorptionCoin();
	//�R�C���̂����蔻��
	void CollisionResponseCoin();
	//�X�e�[�W���C���������n�߂Ă���̃t���[����
	int FlameCnt;
	int m_CoinCnt;//�R�C�����J�E���g
	bool m_absorption_flag;//���@�g���ɋz������邩
	int FlameTime;//���`��Ԃ��J�n�����Ƃ�
	int SEdis;//�L�����N�^�Ƃ̋���
	void update(float data)override;//���t���[��
	//�z������T�C�Y
	const cocos2d::Vec2 AbsorptionSize = cocos2d::Vec2(400.0f, 400.0f);
	cocos2d::Vec2 m_startpos;//���`��ԊJ�n���̃X�^�[�g�̍��W
	cocos2d::Vec2 m_endpos;//�ڕW�̂̍��W
	float AbsorptionPos = 13.0;
	bool m_Move_Flag;//�ړ����邩
	int m_point;//�X�R�A�ɓ���|�C���g
	//���`���
	cocos2d::Vec2 Leap(cocos2d::Vec2 StartPosition, cocos2d::Vec2 GoalPosition, float Time);

	

};

