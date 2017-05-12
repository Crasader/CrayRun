/***************************************************************************
*|
*|	�T�v�@�@���U���g���C���[�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "ResultLayer.h"

USING_NS_CC;

bool ResultLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	//�X�R�A�쐬
	ResultScore* resultscore = ResultScore::create();
	this->addChild(resultscore);
	//�X�R�A���擾����
	resultscore->ScoreAcquisition();
	//�X�R�A�̃����L���O�𒲂ׂ�
	resultscore->RankingSort();
	//�X�R�A�̕ۑ�
	resultscore->ScoreResister();
	//�X�R�A�̐ݒ�A�`��
	for (int i = 0; i < 5; i++)
	{
		resultscore->ScoreIndicate(i);
	}
	this->scheduleUpdate();
	return true;
}



/***************************************************************************
*|	�T�v�@�@�A�b�v�f�[�g�֐�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void ResultLayer::update(float data) {

};