/***************************************************************************
*|
*|	�T�v�@�@UI���C���[�̒�`
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
	log("############################### UILSYER created");

	//������
	m_distanceSpd = 0.18;

	//���C���[�Ƀm�[�h���W��
    distance = Distance::create();
	this->addChild(distance);

	//���C���[�Ƀm�[�h���W��
	score = Score::create();
	this->addChild(score);


	this->scheduleUpdate();



	return true;


}



/***************************************************************************
*|	�T�v�@�@�A�b�v�f�[�g�֐�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void UiLayer::update(float data) {
	//�X�R�A��`��
	score->ScoreIndicate(GameManager::Score);

	//�v���C���[�̑��xx�����̎�
	if (GameManager::PlayerSpd.x > 0.0f)
	{
		//�����𑝂₷
		GameManager::Distance += m_distanceSpd;
		//������`��
		distance->DistanceIndicate(GameManager::Distance);
	}

};