/***************************************************************************
*|
*|	�T�v�@�@�������N���X���`����
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/6/1
*|___________________________________________________________________________
****************************************************************************/
/* ----  �C���N���[�h ---------- */
#include "InfoScene.h"
#include "../TitleScene/TitleScene.h"
#include "../GameManager.h"
#include "audio/include/AudioEngine.h"
/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
//using namespace experimental;
using namespace std;

/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@����
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool InfoScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	
	for (int i = 0; i < MAX_INFOMATION_PASE; i++)
	{
		//�������̃X�v���C�g�����A�ݒ�
		ostringstream ImageName;
		ImageName << "Images/Infomation/Info" << i + 1 << ".png";
		Infomation[i] = Sprite::create(ImageName.str());
		Infomation[i]->setAnchorPoint(Vec2(0, 0));
		Infomation[i]->setPosition(Vec2(i * GameManager::SCREEN_SIZE.x, 0));
		this->addChild(Infomation[i]);
	}
	

	//���֐i�ރ{�^���쐬
	b_Next = ui::Button::create("Images/InfoNext.png");
	b_Next->setPosition(NEXT_POS);
	this->addChild(b_Next);

	//�O�ɖ߂�{�^���쐬
	b_Back = ui::Button::create("Images/InfoBack.png");
	b_Back->setPosition(BACK_POS);
	this->addChild(b_Back);

	//�^�C�g���V�[���ɖ߂�{�^���쐬
	b_BackScene = ui::Button::create("Images/InfoBackScene.png");
	b_BackScene->setPosition(BACK_SCENE_POS);
	this->addChild(b_BackScene);

	//�{�^������Ăяo�����֐���o�^����
	b_Next->addTouchEventListener(CC_CALLBACK_2(InfoScene::OnButtonTouchNext, this));
	b_Back->addTouchEventListener(CC_CALLBACK_2(InfoScene::OnButtonTouchBack, this));

	//����������
	page = 0;
	AnimationCnt = 0;

	//���t���[���Ă�
	this->scheduleUpdate();

	return true;
}





/***************************************************************************
*|	�T�v�@�@���t���[���Ă΂��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void InfoScene::update(float delta)
{
	//�߂�{�^���������ꂽ�Ƃ�
	if (b_BackScene->isHighlighted())
	{
		//���ʉ��Đ�
		experimental::AudioEngine::play2d("Sounds/touch.mp3");
		//�^�C�g���V�[����
		Scene* nextscene = TitleScene::create();
		_director->pushScene(nextscene);
	}


	//�A�j���[�V�����̂��K�v�ȃy�[�W��
	if (page >= 1 && page <= 3)
	{
		//�A�j���[�V�����p�J�E���g���C���N�������g
		AnimationCnt++;
		//10F�Ɉ�x�ʂ�
		if (AnimationCnt % ANIMATION_FLAME)
		{
			Texture2D* texture;
			ostringstream ImageName;
			if (AnimationCnt / ANIMATION_FLAME % 2)
			{
				//�摜�ݒ�
				ImageName << "Images/Infomation/Info" << page+1 << ".png";
				texture = TextureCache::sharedTextureCache()->addImage(ImageName.str());
			}
			else
			{
				//�摜�ݒ�
				ImageName << "Images/Infomation/Info" << page+1 << "_1" <<".png";
				texture = TextureCache::sharedTextureCache()->addImage(ImageName.str());
			}
			//�摜�K�p
			Infomation[page]->setTexture(texture);
		}
		
	}
}



/***************************************************************************
*|	�T�v�@�@�{�^���������ꂽ�Ƃ�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void InfoScene::OnButtonTouchNext(Ref * ref, ui::Widget::TouchEventType eventtype)
{
	switch (eventtype)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED:
		//�y�[�W���Ō�̃y�[�W�ɂȂ��Ă��Ȃ��ꍇ
		if (page < MAX_INFOMATION_PASE - 1)
		{
			//�A�N�V�������s���łȂ��Ƃ�
			if (Infomation[0]->numberOfRunningActions() == 0)
			{
				//�y�[�W���C���N�������g
				page++;
				//�A�j���[�V�����p�J�E���g������������
				AnimationCnt = 0;
				//�S�Ẵy�[�W�ɑ΂��ĉ��Ɉړ�����A�N�V�������s��
				for (int i = 0; i < MAX_INFOMATION_PASE; i++)
				{

					MoveBy* ActionMove = MoveBy::create(1.0f, Vec2(-GameManager::SCREEN_SIZE.x, 0));
					Infomation[i]->runAction(ActionMove);
				}
				//�X���C�h���Đ�
				experimental::AudioEngine::play2d("Sounds/SlideSE.ogg");
			}
		}
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}



/***************************************************************************
*|	�T�v�@�@�{�^���������ꂽ�Ƃ�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void InfoScene::OnButtonTouchBack(Ref * ref, ui::Widget::TouchEventType eventtype)
{
	switch (eventtype)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED:
			//�y�[�W���ŏ��̃y�[�W�ɂȂ��Ă��Ȃ��ꍇ
			if (page != 0)
			{
				//�A�N�V�������s���łȂ��Ƃ�
				if (Infomation[0]->numberOfRunningActions() == 0)
				{
					//�y�[�W���f�N�������g
					page--;
					//�A�j���[�V�����p�J�E���g������������
					AnimationCnt = 0;
					//�S�Ẵy�[�W�ɑ΂��ĉ��Ɉړ�����A�N�V�������s��
					for (int i = 0; i < MAX_INFOMATION_PASE; i++)
					{
						MoveBy* ActionMove = MoveBy::create(1.0f, Vec2(GameManager::SCREEN_SIZE.x, 0));
						Infomation[i]->runAction(ActionMove);
					}
					//�X���C�h���Đ�
					experimental::AudioEngine::play2d("Sounds/SlideSE.ogg");

				}
			}
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
