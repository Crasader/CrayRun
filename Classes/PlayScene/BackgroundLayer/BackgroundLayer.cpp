/***************************************************************************
*|
*|	�T�v�@�@���U���g���C���[
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "BackgroundLayer.h"
/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;

bool BackgroundLayer::init()
{
	if (!Layer::init()) {

		return false;

	}

	//���C���[�Ƀm�[�h���W��
	Background* background = Background::create();
	this->addChild(background);




	//���t���[���Ăяo��
	this->scheduleUpdate();
	return true;

}



void BackgroundLayer::update(float data) 
{

};
