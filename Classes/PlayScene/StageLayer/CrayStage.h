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
#include "GameManager.h"
class CrayStage :public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(CrayStage);
	//�S�y��
	cocos2d::Sprite* cryfloor;
	//�T�C�Y�ύX
	void SetScale();
private:
	//�S�y���̃J�E���g
	int CryFloorCnt;
	//
	std::vector<cocos2d::Vec2> CrayStagePos;


};

