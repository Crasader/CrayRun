
/***************************************************************************
*|
*|	�T�v�@���U���g�V�[���̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "ResultScene.h"
#include "ResultScore.h"
#include "ResultLayer.h"
#include "EventListenerGesture.h"




/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;




bool ResultScene::init(int score, int distance)
{
	// �e�N���X������������
	if (!Scene::init())
	{
		return false;
	}

	// �^�b�`�C�x���g���X�i�[���쐬
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ResultScene::onTouchBegan, this);
	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//����̃X�R�A���i�[����
	ResultScore::m_Score = score;
	ResultScore::m_distance = distance;
	log("############################### ResultScene created");
	//ResultLayer���W��
	ResultLayer* resultlayer = ResultLayer::create();
	this->addChild(resultlayer);
	return true;
}

/* ---- �����o�[�֐��̒�` ---------------- */
/***************************************************************************
*|	�T�v�@�@�V�[�����쐬����B
*|	�����@�@����
*|�@�߂�l�@�V�[���̃A�h���X
****************************************************************************/
Scene* ResultScene::create(int score,int distance)
{
	//�������m��
	ResultScene *pRet = new(std::nothrow)ResultScene();

	if (pRet && pRet->init(score,distance))
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


/***************************************************************************
*|	�T�v�@�@�L�[�������ꂽ�Ƃ��Ăяo�����֐�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
// �^�b�`�J�n���R�[���o�b�N
bool ResultScene::onTouchBegan(Touch* touch, Event* pEvent)
{

	////�t�F�[�h�g�����W�V����
	//nextScene = TransitionOriginal::create(1.0f, nextScene);
	//if (Score::SceneFlag == true)
	//{
	//	Score::SceneFlag = false;
	//	// ���̃V�[�����쐬����
	//	Scene* nextScene = TitleScene::create();
	//	// ���̃V�[���Ɉڍs
	//	_director->replaceScene(nextScene);
	//}


	return true;

}
