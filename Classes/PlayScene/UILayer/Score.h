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
#include "../../GameManager.h"

static const int MAX_NUMBER = 5;

class Score :public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(Score);

	//�X�R�A�̐ݒ�A�`��
	void ScoreIndicate(int Score);

private:
	//�����X�v���C�g
	cocos2d::Sprite* s_Number[MAX_NUMBER];
	int ScoreMaxDigit;//�ő包��
	int SaveScore;//�X�R�A��ۑ�����
	int Digit;//����
	int SpriteCnt;//���ڂ̃X�v���C�g���J�E���g����

};

