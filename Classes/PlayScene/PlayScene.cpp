/***************************************************************************
*|
*|	�T�v�@�@�v���C�V�[���N���X�̒�`
*|�@�쐬�ҁ@GF3 17 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/

/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "PlayScene.h"

USING_NS_CC;
using namespace cocos2d::experimental;

/* ---- �����o�[�֐��̒�` ---------------- */
/***************************************************************************
*|	�T�v�@�@�V�[�����쐬����B
*|	�����@�@����
*|�@�߂�l�@�V�[���̃A�h���X
****************************************************************************/
//cocos2d::Scene * PlayScene::createScene()
//{
//	// �V�[�����쐬����
//
//	auto scene = Scene::create();
//	// ���C���[���쐬����
//
//	auto layer = PlayScene::create();
//	// ���C���[���V�[���ɒǉ�����
//
//	scene->addChild(layer);
//	// �V�[����Ԃ�
//
//	return scene;
//}

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
	auto stagelayer = StageLayer::create();
	// �X�e�[�W���C���[�֘A�̃��C���[
	this->addChild(stagelayer);
	// �L�����N�^�[���C���[�Ăяo��
	auto characterlayer = CharacterLayer::create();
	// �w�i���C���[�֘A�̃��C��
	this->addChild(characterlayer);
	// UI���C���[�Ăяo��
	uilayer = UiLayer::create();
	// UI���C���[�֘A�̃��C��
	this->addChild(uilayer);

	Camera* camera = Camera::create();
	camera->setCameraFlag(CameraFlag::USER1);
	this->addChild(camera);

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
	//�f�t�H���g�J������ݒ肷��
	PlayScene::m_camera = this->getDefaultCamera();
	//�J�������W���A���t���[��������
	GameManager::m_cameraposx += GameManager::m_cameraspdx;
	//�J�����̍��W���Z�b�g
	PlayScene::m_camera->setPositionX(GameManager::m_cameraposx);


	uilayer->setCameraMask((unsigned short)CameraFlag::USER1);

}


