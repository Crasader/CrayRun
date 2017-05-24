/***************************************************************************
*|
*|	�T�v�@�@���U���g���C���[�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "ResultLayer.h"
#include "../TiTleScene/TitleScene.h"

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
	if (m_resultscore->TitleFlag == true)
	{
		if (CreateSprite == false)
		{
			//�X�v���C�g�̐���
			s_touch = Sprite::create("Images/TouchImage.png");
			s_touch->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 2, 50));
			addChild(s_touch);
			CreateSprite = true;
		}
		VisibleCnt+=3;
		s_touch->setOpacity(VisibleCnt);
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
	if (m_resultscore->RankingFlag == true)
	{
		m_resultscore->ResultOutAction();
		//��x�����ʂ�Ȃ�
		m_resultscore->RankingFlag = false;

		MoveBy* ScoreAction = MoveBy::create(0.5f, Vec2(0, 700));
		nowscore_background->runAction(ScoreAction);
	}
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
	if (m_resultscore->TitleFlag == true)
	{
		

		Scene* nextScene = TitleScene::create();

		_director->replaceScene(nextScene);
	}
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