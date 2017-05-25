#include "Gnome.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

bool Gnome::init()
{
	if (!Character::init())
	{
		return false;
	}
	GameManager::ScoreCorrection = 1.2f;
	// ���ʂ̉摜����ύX
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/Gnome_Chara.png");

	s_player->setTexture(texture);
	s_player->setContentSize(texture->getContentSize());

	JumpSize = 11.0f;
	return true;
}

/// <summary>
/// �A�j���[�V��������֐��i�p���j
/// </summary>


void Gnome::Animation()
{
	//�A�j���[�V��������
	Texture2D* texture;
	//�W�����v�ł���Ƃ����W�����v���܂����Ă��Ȃ��Ƃ��i�����Ă�Ƃ��j
	if (JumpCnt == 0 && JumpFlag == true)
	{
		switch (walkCnt / AnimationSpd % 4)
		{
		case 0:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Gnome_Chara.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());

			break;
		case 1:
		case 3:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Gnome_Chara2.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());
			break;
		case 2:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Gnome_Chara3.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());
			break;
		}
	}
	else
	{
		texture = TextureCache::sharedTextureCache()->addImage("Images/Gnome_Charaj.png");

		s_player->setTexture(texture);
		s_player->setContentSize(texture->getContentSize());
	}
}
