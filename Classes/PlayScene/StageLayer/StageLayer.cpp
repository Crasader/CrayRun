/***************************************************************************
*|
*|	�T�v�@�@���U���g���C���[
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "StageLayer.h"

USING_NS_CC;

bool StageLayer::init()
{
	if (!Layer::init()) {

		return false;

	}

	//���C���[�Ƀm�[�h���W��
	Coin* coin = Coin::create();
	this->addChild(coin);

	//���C���[�Ƀm�[�h���W��
	CrayStage* craystage = CrayStage::create();
	this->addChild(craystage);


	//���C���[�Ƀm�[�h���W��
	Stage* stage = Stage::create();
	this->addChild(stage);



	this->scheduleUpdate();


	return true;

}



void StageLayer::update(float data) {};