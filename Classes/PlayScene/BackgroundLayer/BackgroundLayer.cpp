/***************************************************************************
*|
*|	�T�v�@�@�w�i���U���g���C���[
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  �C���N���[�h ---------- */
#include "BackgroundLayer.h"
#include "../../GameManager.h"
/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;


/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@����
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool BackgroundLayer::init()
{
	if (!Layer::init()) {

		return false;

	}

	//���C���[�Ƀm�[�h���W��
	background = Background::create();
	this->addChild(background);




	//���t���[���Ăяo��
	this->scheduleUpdate();
	return true;

}



void BackgroundLayer::update(float data) 
{
	if (GameManager::m_cameraposx == 480 + GameManager::m_cameraspdx)
	{

		background->scheduleUpdate();
	}
};
