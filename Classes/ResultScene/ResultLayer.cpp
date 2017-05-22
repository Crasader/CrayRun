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

	//�w�i
	Sprite* backcoin = Sprite::create("Images/Result.png");
	backcoin->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 2, GameManager::SCREEN_SIZE.y / 2));
	backcoin->setScale(1.5f, 1.4f);
	this->addChild(backcoin);

	//�w�i
	nowscore_background = Sprite::create("Images/NowScore.png");
	nowscore_background->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 2, GameManager::SCREEN_SIZE.y / 2));
	this->addChild(nowscore_background);






	//�X�R�A�쐬
	m_resultscore = ResultScore::create();
	this->addChild(m_resultscore);
	//����̃X�R�A�̃A�N�V����
	m_resultscore->ScoreAction(-1);

	//�X�R�A���擾����
	m_resultscore->ScoreAcquisition();
	//�X�R�A�̃����L���O�𒲂ׂ�
	m_resultscore->RankingSort();
	//�X�R�A�̕ۑ�
	m_resultscore->ScoreResister();



	//����̃X�R�A�A�����A���v�X�R�A���i�[����
	int nowscore[3] = { ResultScore::m_Score,ResultScore::m_distance,ResultScore::m_Score + ResultScore::m_distance };
	for (int i = 0; i < 3; i++)
	{

		m_resultscore->ScoreIndicate2(nowscore[i]);

		m_resultscore->ScoreMaxDigit = 0;
		m_resultscore->now_number++;

	}

	//�X�R�A�̐ݒ�A�`��
	for (int i = 0; i < 5; i++)
	{
		m_resultscore->ScoreIndicate(i);
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
void ResultLayer::update(float data)
{
	if (m_resultscore->RankingFlag == true)
	{

		//����̐����X�v���C��
		cocos2d::Sprite* s_now_number;
		for (int i = 0; i < 3; i++)
		{
			MoveBy* ResultAction = MoveBy::create(3.0f, Vec2(0.0f, 300.0f));
			m_resultscore->now_node_number[i]->runAction(ResultAction);
		}
	
	}
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