/***************************************************************************
*|
*|	�T�v�@�@�^�C�g�����C���N���X���`����
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017//
*|___________________________________________________________________________
****************************************************************************/
/* ---- �C���N���[�h ---------- */
#include "TitleLayer.h"
#include "../PlayScene/PlayScene.h"
#include "../InfoScene/InfoScene.h"
#include "../GameManager.h"
#include "TitleCharacter.h"
#include "audio\include\AudioEngine.h"
/* ---- ���d�C���N���[�h�̖h�~ ---------- */
USING_NS_CC;


/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@����
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool TitleLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	//�w�i�X�v���C�g
	Sprite* s_background = Sprite::create("Images/TitleBackground.png");
	s_background->setAnchorPoint(Vec2(0,0));
	this->addChild(s_background);

	//�X�^�[�g�{�^��
	b_start = ui::Button::create("Images/StartImage.png");
	b_start->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 3, 200));
	b_start->setScale(0.8, 0.8);
	this->addChild(b_start);

	//�����{�^��
	b_info = ui::Button::create("Images/InfoImage.png");
	b_info->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 3 * 1.5, 100));
	b_info->setScale(0.8, 0.8);
	this->addChild(b_info);

	//�I���{�^��
	b_exit = ui::Button::create("Images/ExitImage.png");
	b_exit->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 3 * 2, 200));
	b_exit->setScale(0.8, 0.8);
	this->addChild(b_exit);

	//�^�C�g���L�����N�^�̍쐬
	TitleChracter* titlecharacter = TitleChracter::create();
	this->addChild(titlecharacter);

	//////�������Đ�������
	TitleBgm = experimental::AudioEngine::play2d("Sounds/TitleBGMLoop.ogg",true);
	//experimental::AudioEngine::setLoop(TitleBgm,true);
	//���y�I�u�W�F�N�g����


	this->scheduleUpdate();
	return true;
}


void TitleLayer::update(float delta)
{
	//�X�^�[�g�{�^���������ꂽ��
	if (b_start->isHighlighted())
	{
		//���y�~�߂�
		experimental::AudioEngine::stop(TitleBgm);
		experimental::AudioEngine::play2d("Sounds/touch.mp3");
		//�������Đ�������
		//experimental::AudioEngine::setFinishCallback(touchAudio,CC_CALLBACK_0(TitleLayer::IsuncacheAll,this));


		//����������
		GameManager::Initialize();

		////�v���C�V�[����
		Scene* nextscene = PlayScene::create();
		_director->pushScene(nextscene);
	
	}
	//������
	if (b_info->isHighlighted())
	{

		//BGM���~�߂�
		experimental::AudioEngine::stop(TitleBgm);
		experimental::AudioEngine::play2d("Sounds/touch.mp3");

		//�����L���b�V��
	//	experimental::AudioEngine::uncacheAll();
		Scene* nextscene = InfoScene::create();
		_director->pushScene(nextscene);
	}

	//�I���{�^���������ꂽ��
	if (b_exit->isHighlighted()) 
	{
		
		experimental::AudioEngine::play2d("Sounds/touch.mp3");

		_director->end();
	}
}

