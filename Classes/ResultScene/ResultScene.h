/***************************************************************************
*|
*|	�T�v�@���U���g�V�[���̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/5/10
*|___________________________________________________________________________
****************************************************************************/

#pragma once

/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "cocos2d.h"
#include "../GameManager.h"

class ResultScene :public cocos2d::Scene
{
public:
	//�V�[�����쐬����
	static cocos2d::Scene* create(int score, int distance);
	//����������
	 bool init(int score,int distance);

private:
	//�^�b�`���ꂽ��
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent);
	////���t���[���Ă΂��
	//void update(float data)override;


};