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
	std::vector<cocos2d::Sprite*> crayfloor;
	//�T�C�Y�ύX
	//void SetScale();
	//�T�C�Y
	std::vector<cocos2d::Vec2>CrayStageSize;
private:
	//�S�y���̃J�E���g
	int CryFloorCnt;
	//����̍��W
	std::vector<cocos2d::Vec2> CrayStagePos;


};

