//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//
//�@�t�@�C�����FRabbitMold.h
//
//	�T�@�@�@�v�F�e�^�̋��^
//
//�@��@���@�ҁFGS2 24 �R�{�I��
//
//�@��@���@���F2017/05/02
//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
//���C�u�����̃C���N���[�h/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "cocos2d.h"
#include "GameManager.h"

class Mold : public cocos2d::Node {

public:
	virtual bool init();

	CREATE_FUNC(Mold);
	cocos2d::Sprite* s_Mold;//�R�C��
	int m_MoldCnt = 0;


	//�d��


private:

};