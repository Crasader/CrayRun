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
#include"../../GameManager.h"

const int DISTANCE_MAX_NUMBER = 5;//�����̃X�v���C�g�̐�

class Distance :public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(Distance);

	//�����̐ݒ�A�`��
	void DistanceIndicate(int distance);

private:
	//�����X�v���C�g
	cocos2d::Sprite* s_Number[DISTANCE_MAX_NUMBER];

};

