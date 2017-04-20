/***************************************************************************
*|
*|	�T�v�@�@���U���g���C���[
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "UiLayer.h"

USING_NS_CC;

bool UiLayer::init()
{
	if (!Layer::init()) {

		return false;

	}

	//���C���[�Ƀm�[�h���W��
	Distance * distance = Distance::create();
	this->addChild(distance);

	//���C���[�Ƀm�[�h���W��
	Score* score = Score::create();
	this->addChild(score);

	this->scheduleUpdate();


	return true;


}



void UiLayer::update(float data) {};