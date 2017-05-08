/***************************************************************************
*|
*|	�T�v�@�@�ΖʃN���X�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
#pragma once
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"
class Slope :public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(Slope);

private:
	//�Ζʕ�
	cocos2d::Vec2 SlopeSize;
	//�ΖʃX�v���C�g
	cocos2d::Sprite* s_slope;
	//�C�e���[�^
	cocos2d::Vector<cocos2d::Vec2>::iterator IteratorRight;
	cocos2d::Vector<cocos2d::Vec2>::iterator IteratorLeft;

	//�o��
	bool ClimbingFlag;


	//�C�e���[�^�̒l���i�[����
	cocos2d::Vec2 SaveRight;
	cocos2d::Vec2 SaveLeft;


};
