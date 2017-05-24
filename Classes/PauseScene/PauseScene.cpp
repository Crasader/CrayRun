
/***************************************************************************
*|
*|	�T�v�@���U���g�V�[���̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */

#include "EventListenerGesture.h"
#include "PauseScene.h"
#include "../PlayScene/PlayScene.h"
#include "../TitleScene/TitleScene.h"
/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;


bool PauseScene::init()
{
	// �e�N���X������������
	if (!Scene::init())
	{
		return false;
	}

	// �^�b�`�C�x���g���X�i�[���쐬
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(PauseScene::onTouchBegan, this);
	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	

	//�Â���{�^�����쐬����
	CountinueButton = ui::Button::create("Images/pause1.png");
	CountinueButton->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 2,450));
	this->addChild(CountinueButton);

	

	//�^�C�g���{�^�����쐬����
	TitleButton = ui::Button::create("Images/pause2.png");
	TitleButton->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 2, 250));
	this->addChild(TitleButton);
	
	this->scheduleUpdate();

	return true;
}
void PauseScene::update(float data)
{

	if (CountinueButton->isHighlighted())
	{
		_director->popScene();
	}

	if (TitleButton->isHighlighted())
	{
		GameManager::Initialize();
		Scene* nextscene = TitleScene::create();
		_director->pushScene(nextscene);
	}
}
/* ---- �����o�[�֐��̒�` ---------------- */

/***************************************************************************
*|	�T�v�@�@�L�[�������ꂽ�Ƃ��Ăяo�����֐�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
// �^�b�`�J�n���R�[���o�b�N
bool PauseScene::onTouchBegan(Touch* touch, Event* pEvent)
{

	_director->popScene();


	return true;

}
