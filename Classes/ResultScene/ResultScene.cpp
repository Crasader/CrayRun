/***************************************************************************
*|
*|	�T�v�@���U���g�V�[���̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/5/10
*|___________________________________________________________________________
****************************************************************************/
#pragma execution_character_set("utf-8")

/* ----  �C���N���[�h ---------- */
#include "ResultScene.h"
#include "ResultScore.h"
#include "EventListenerGesture.h"

#if (CC_TAGET_PLATFORM == CC_PLATFORM_ANDROID)
#define YUSUKE_FONT "meiryo.ttc"
#else
#define YUSUKE_FONT "Meiryo"
#endif 



/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;

//using namespace ui;

/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@����
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
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
	resultlayer = ResultLayer::create();
	this->addChild(resultlayer);


	//���t���[���Ă�
	this->scheduleUpdate();
	

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

void ResultScene::editBoxEditingDidBegin(cocos2d::ui::EditBox * editBox)
{
}

void ResultScene::editBoxEditingDidEnd(cocos2d::ui::EditBox * editBox)
{
}

void ResultScene::editBoxTextChanged(cocos2d::ui::EditBox * editBox, const std::string & text)
{
}

void ResultScene::editBoxReturn(cocos2d::ui::EditBox * editBox)
{
	
		//���񃉃��L���O�C�������v���C���[�����i�[����
		ResultScore::Now_Player_Name = editBox->getText();

		//���͂��I�����
		resultlayer->InputNameEndFlag = true;
		//�w�i������
		InputNameBackGround->removeFromParent();
		//���E�̂ǁ[�낭�������
		left_dorokun->removeFromParent();
		right_dorokun->removeFromParent();

		//���U���g���C�����ċN��
		//resultlayer->resume();
		//�L�[�{�[�h���ӂ��Ƃ΂�
		editBox->setPosition(Vec2(1000,1000));
		//���U���gBGM���ĊJ
		experimental::AudioEngine::resume(resultlayer->ResoultBgm);
}

void ResultScene::update(float data)
{
	//���͂���^�C�~���O��
	if (resultlayer->InputNameFlag == true)
	{
		//���U���gBGM���~�߂�
		experimental::AudioEngine::pause(resultlayer->ResoultBgm);
			
		//��񂫂񂮖��̉摜
		InputNameBackGround = Sprite::create("Images/InputBackGround.png");
		InputNameBackGround->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 2, GameManager::SCREEN_SIZE.y / 2));
		this->addChild(InputNameBackGround);

		//�h�[���N�̉摜�i���E�j
		left_dorokun = Sprite::create("Images/Player_w.png");
		right_dorokun = Sprite::create("Images/Player_w.png");

		//�w�i�̃h�[���N�̍��W�ɍ��킹��
		left_dorokun->setPosition(Vec2(119.0f, 163.0f));
		right_dorokun->setPosition(Vec2(832.0f, 176.0f));
		//�E���̃h�[���N�𔽓]������(X)
		right_dorokun->setFlipX(true);

		this->addChild(left_dorokun);
		this->addChild(right_dorokun);

		//�_�ł���A�N�V����
		Hide* left_hideaction = Hide::create();
		Show* left_showaction = Show::create();
		DelayTime* left_delayaction = DelayTime::create(0.5f);
		Sequence* left_flashing_action = Sequence::create(left_hideaction, left_delayaction, left_showaction, left_delayaction, nullptr);
		RepeatForever* left_repeat_action = RepeatForever::create(left_flashing_action);
		//�_�ł���A�N�V����(�E�p)
		Hide* right_hideaction = Hide::create();
		Show* right_showaction = Show::create();
		DelayTime* right_delayaction = DelayTime::create(0.5f);
		Sequence* right_flashing_action = Sequence::create(right_hideaction, right_delayaction, right_showaction, right_delayaction, nullptr);
		RepeatForever* right_repeat_action = RepeatForever::create(right_flashing_action);

		left_dorokun->runAction(left_repeat_action);
		right_dorokun->runAction(right_repeat_action);

		ui::EditBox * editBox = ui::EditBox::create(Size(400, 60), "Images/Input.png");
		editBox->setFont(YUSUKE_FONT, 24);
		//editBox->setPlaceHolder("���Ȃ܂�");
		editBox->setFontColor(Color4B(0, 0, 0, 255));
		editBox->setMaxLength(6);
		//editBox->setText("�������^�b�`�Ŗ��O����");
		editBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
		editBox->setScale(1.3f, 1.2f);
		//editBox->setInputMode(ui::EditBox::InputMode::ANY);
		editBox->setPosition(Vec2(200.0f, 150.0f));
		editBox->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		editBox->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
		editBox->setDelegate(this);
	
		this->addChild(editBox);


		//��񂵂��ʂ�Ȃ�
		resultlayer->InputNameFlag = false;
	}
}
