
/***************************************************************************
*|
*|	�T�v�@���U���g�V�[���̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/5/10
*|___________________________________________________________________________
****************************************************************************/
#pragma execution_character_set("utf-8")

/* ---- ���C�u�����̃C���N���[�h ---------- */
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
	

	//EditBox * editBox = EditBox::create(Size(400, 60), "Images/coin1.png");
	//editBox->setFont("arial", 24);
	//editBox->setPlaceHolder("aaa");
	//editBox->setFontColor(Color4B(0, 0, 0, 255));
	//editBox->setMaxLength(16);
	//editBox->setText("aaaa");
	//editBox->setReturnType(EditBox::KeyboardReturnType::DONE);
	//editBox->setInputMode(EditBox::InputMode::SINGLE_LINE);
	//editBox->setPosition(Vec2(480.0f, 320.0f));
	//editBox->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	//editBox->setDelegate(this);

	//this->addChild(editBox);
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
		//
		InputNameBackGround->removeFromParent();
		//���U���g���C�����ċN��
		//resultlayer->resume();
		//�L�[�{�[�h���ӂ��Ƃ΂�
		editBox->setPosition(Vec2(1000,1000));

}

void ResultScene::update(float data)
{
	//���͂���^�C�~���O��
	if (resultlayer->InputNameFlag == true)
	{
		//���U���g�V�[�����~�߂�
		//resultlayer->pause();
		//��񂫂񂮖��̉摜
		InputNameBackGround = Sprite::create("Images/InputBackGround.png");
		InputNameBackGround->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 2, GameManager::SCREEN_SIZE.y / 2));
		this->addChild(InputNameBackGround);

		ui::EditBox * editBox = ui::EditBox::create(Size(400, 60), "Images/Input.png");
		editBox->setFont(YUSUKE_FONT, 24);
		//editBox->setPlaceHolder("���Ȃ܂�");
		editBox->setFontColor(Color4B(0, 0, 0, 255));
		editBox->setMaxLength(6);
		//editBox->setText("�������^�b�`�Ŗ��O����");
		editBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
		editBox->setScale(1.3f, 1.2f);
		editBox->setInputMode(ui::EditBox::InputMode::ANY);
		editBox->setPosition(Vec2(200.0f, 150.0f));
		editBox->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		editBox->setDelegate(this);
	
		this->addChild(editBox);


		//��񂵂��ʂ�Ȃ�
		resultlayer->InputNameFlag = false;
	}
}
