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

	JumpSize = 9.0f;
	return true;
}

/// <summary>
/// �ړ�����֐��i�p���j
/// </summary>
void Gnome::Move()
{
	//���N���X��Move���Ăяo��
	Character::Move();
	
	//�A�j���[�V��������
	Texture2D* texture;
	switch (walkCnt / 10 % 4)
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
