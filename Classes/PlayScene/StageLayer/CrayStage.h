/***************************************************************************
*|
*|	�T�v�@�@�X�R�A�N���X�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once
/* ----  �C���N���[�h ---------- */
#include "cocos2d.h"
#include "GameManager.h"
#include "CrayStageSprite.h"

class CrayStage :public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(CrayStage);
	//�T�C�Y�ύX
	//void SetScale();
	//�S�y��
	std::vector<CrayStageSprite*> m_crayfloor;
private:
	
	//����̍��W
	std::vector<cocos2d::Vec2> CrayStagePos;


};

