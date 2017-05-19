/***************************************************************************
*|
*|	�T�v�@�@���U���g���C���[�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "ResultLayer.h"
#include "../PlayScene/PlayScene.h"

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

	// Register Touch Event
	EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(ResultLayer::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(ResultLayer::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(ResultLayer::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(ResultLayer::onTouchesCancelled, this);

	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();
	return true;
}

/***************************************************************************
*|	�T�v�@�@�A�b�v�f�[�g�֐�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void ResultLayer::update(float data) {
		
}
/***************************************************************************
*|	�T�v�@�@�^�b�`���ꂽ���ɌĂԊ֐�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void ResultLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesBegan");
}
/***************************************************************************
*|	�T�v�@�@�^�b�`���Ă��ē������Ƃ��ɌĂԊ֐�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void ResultLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesMoved");
}
/***************************************************************************
*|	�T�v�@�@�^�b�`���ꂽ�̂𗣂������ɌĂԊ֐�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void ResultLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	GameManager::Initialize();

	Scene* nextScene = PlayScene::create();

	_director->replaceScene(nextScene);
}
/***************************************************************************
*|	�T�v�@�@�^�b�`���Ă���̂��L�����Z�������Ƃ��ɌĂԊ֐�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void ResultLayer::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesCancelled");
}