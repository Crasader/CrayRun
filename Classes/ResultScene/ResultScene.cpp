#include "ResultScene.h"
#include "ResultScore.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;


bool ResultScene::init(int score)
{
	// �e�N���X������������
	if (!Scene::init())
	{
		return false;
	}


	ResultScore::m_Score = score;
	log("############################### ResultScene created");
	//ResultLayer���W��
	ResultLayer* resultlayer = ResultLayer::create();
	this->addChild(resultlayer);
	return true;
}

//void ResultScene::update(float data)
//{
//}
/* ---- �����o�[�֐��̒�` ---------------- */
/***************************************************************************
*|	�T�v�@�@�V�[�����쐬����B
*|	�����@�@����
*|�@�߂�l�@�V�[���̃A�h���X
****************************************************************************/
Scene* ResultScene::create(int score)
{
	//�������m��
	ResultScene *pRet = new(std::nothrow)ResultScene();

	if (pRet && pRet->init(score))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}

}