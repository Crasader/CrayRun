/***************************************************************************
*|
*|	�T�v�@�@�X���C���N���X���`����
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/6/1
*|___________________________________________________________________________
****************************************************************************/


/* ----  �C���N���[�h ---------- */

#include "Slime.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@����
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool Slime::init()
{
	if (!Character::init())
	{

		return false;
	}
	//�X�R�A�̔{����ݒ�
	GameManager::ScoreCorrection = SCORECORRECTION;
	// ���ʂ̉摜����ύX
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/slime_chara.png");

	s_player->setTexture(texture);
	s_player->setContentSize(texture->getContentSize());

	JumpSize = JUMPSIZE;

	return true;
}

void Slime::Animation()
{
	Texture2D* texture;

	//�W�����v�ł���Ƃ����W�����v���܂����Ă��Ȃ��Ƃ��i�����Ă�Ƃ��j
	if (GameManager::JumpCnt == 0 && GameManager::JumpFlag == true)
	{
		switch (walkCnt / 7 % 4)
		{
		case 0:
			texture = TextureCache::sharedTextureCache()->addImage("Images/slime_chara2.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());

			break;
		case 1:
		case 3:
			texture = TextureCache::sharedTextureCache()->addImage("Images/slime_chara.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());

			break;
		case 2:
			texture = TextureCache::sharedTextureCache()->addImage("Images/slime_chara3.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());

			break;
		}
	}
	else {
		texture = TextureCache::sharedTextureCache()->addImage("Images/slime_charaj.png");

		s_player->setTexture(texture);
		s_player->setContentSize(texture->getContentSize());
	}
}
