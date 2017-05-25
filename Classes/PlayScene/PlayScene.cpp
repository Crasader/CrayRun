/***************************************************************************
*|
*|	�T�v�@�@�v���C�V�[���N���X�̒�`
*|�@�쐬�ҁ@GF3 17 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/

/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "PlayScene.h"
/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

/* ---- �����o�[�֐��̒�` ---------------- */
/***************************************************************************
*|	�T�v�@�@�v���C�V�[���̃��C���[���Ăт���
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
bool PlayScene::init()
{
	// �e�N���X������������
	if (!Scene::init())
	{
		return false;
	}
	// �w�i���C���[�Ăяo��
	auto backgroundlayer = BackgroundLayer::create();
	// �w�i���C���[�֘A�̃��C���[
	this->addChild(backgroundlayer);
	// �X�e�[�W���C���[�Ăяo��
	stagelayer = StageLayer::create();
	// �X�e�[�W���C���[�֘A�̃��C���[
	this->addChild(stagelayer);
	// �L�����N�^�[���C���[�Ăяo��
	characterlayer = CharacterLayer::create();
	// �L�����N�^�[���C���[�֘A�̃��C��
	this->addChild(characterlayer);
	// UI���C���[�Ăяo��
	uilayer = UiLayer::create();
	// UI���C���[�֘A�̃��C��
	this->addChild(uilayer);

	//�J�������쐬����
	Camera* camera = Camera::create();
	camera->setCameraFlag(CameraFlag::USER1);
	this->addChild(camera);


	//// �ꎞ��~
	//cocos2d::Director::getInstance()->pause();
	//cocos2d::Director::getInstance()->isPaused();


	//�}�b�v�摜����
	for (int i = 1; i <= 3; i++)
	{
		std::ostringstream MapName;
		MapName<< "Images/" << i << ".png";
		Number[i-1] = Sprite::create(MapName.str());
		Number[i-1]->setPosition(GameManager::SCREEN_SIZE / 2);
		Number[i-1]->setVisible(false);
		this->addChild(Number[i-1]);
	}

	//GO�摜����
	Go = Sprite::create("Images/GO.png");
	Go->setPosition(GameManager::SCREEN_SIZE / 2);
	Go->setVisible(false);
	this->addChild(Go);

	
	//update�֐����Ă�
	this->scheduleUpdate();

	return true;
}

/***************************************************************************
*|	�T�v�@�@���t���[���Ă΂��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void PlayScene::update(float data)
{

	if (StopFlag == false)
	{
		StopFlag = true;
		//�J�E���g�_�E��������
		NumberAction(3);
		//�L�����N�^���C�����~�߂�
		characterlayer->pause();
		//UI���C�����~�߂�
		uilayer->pause();
		//�X�e�[�W���C�����~�߂�
		stagelayer->pause();
	}

	if (m_CameraFlag == true)
	{
		//�f�t�H���g�J������ݒ肷��
		PlayScene::m_camera = this->getDefaultCamera();
		//�J�������W���A���t���[��������
		GameManager::m_cameraposx += GameManager::m_cameraspdx;
		GameManager::WorldPosX += GameManager::m_cameraspdx;
		//�J�����̍��W���Z�b�g
		PlayScene::m_camera->setPositionX(GameManager::m_cameraposx);

		//UI��p�̃J�����ɂ���
		uilayer->setCameraMask((unsigned short)CameraFlag::USER1);
	}


	//��ʍ��������͉�ʉ��ɏo���烊�U���g�V�[���ֈڍs
	if (GameManager::PlayerPos.y < 0 ||  GameManager::PlayerPos.x <= GameManager::WorldPosX || GameManager::GameOverFlag == true)
	{

		//�L�����N�^���C�����~�߂�
		characterlayer->pause();
		//UI���C�����~�߂�
		uilayer->pause();
		//�X�e�[�W���C�����~�߂�
		//�J�������~�߂�
		m_CameraFlag = false;
		//�|�[�Y�@�\�g�p�s��
		GameManager::CountDownFlag = false;

		//�G�t�F�N�g����
		Effect = Sprite::create("Images/EndEffect.png");
		Effect->setPosition(GameManager::PlayerPos.x + GameManager::PlayerSize.x, GameManager::PlayerPos.y + GameManager::PlayerSize.y / 2);
		this->addChild(Effect);

		//�����~�߂Ă���V�[���ȍ~
		DelayTime* action = DelayTime::create(1.0f);
		CallFunc* action2 = CallFunc::create(CC_CALLBACK_0(PlayScene::TransitionPlayToResult, this));
		Sequence* action3 = Sequence::create(action, action2, nullptr);
		this->runAction(action3);
	}

}


//�����̃A�N�V�����ċN�֐�
void PlayScene::NumberAction(int cnt)
{
	//�҂A�\���A�����A������A�֐��ĂԂ����Ԃ�
	DelayTime* action = DelayTime::create(0.5f);
	Show* action2 = Show::create();
	MoveBy* action3 = MoveBy::create(0.4f, Vec2(0.0f, -50.0f));
	RemoveSelf* action4 = RemoveSelf::create();
	CallFunc* action5 = CallFunc::create(CC_CALLBACK_0(PlayScene::NumberAction, this, --cnt));
	Sequence* action6 = Sequence::create(action, action2, action3, action4, action5,  nullptr);
	
	//Go�̃A�N�V�����Ƃ��Ď��s
	if (cnt == -1)
	{
		Go->runAction(action6);
	}
	
	//�S�ďI�������J�����𓮂���
	else if (cnt == -2)
	{
		//�J�����𓮂���
		m_CameraFlag = true;
		//�L�����N�^���C�����Ďn������
		characterlayer->resume();
		//UI���C�����Ďn������
		uilayer->resume();
		//�X�e�[�W�̍Ďn������
		stagelayer->resume();
		//�|�[�Y�@�\���ł���悤�ɂ���
		GameManager::CountDownFlag = true;
	}
	//�J�E���g�Ƃ��ăA�N�V���������s
	
	if (cnt >= 0)
	{
		Number[cnt]->runAction(action6);
	}
}


