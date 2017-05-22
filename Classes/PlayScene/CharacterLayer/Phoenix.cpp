#include "Phoenix.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

bool Phoenix::init()
{
	if (!Character::init())
	{
		return false;
	}
	GameManager::ScoreCorrection = 1.3f;
	// ���ʂ̉摜����ύX
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/Phoenix_Chara.png");

	s_player->setTexture(texture);
	s_player->setContentSize(texture->getContentSize());

	JumpSize = 11.0f;
	return true;
}

void Phoenix::Move()
{
	//���N���X��Move���Ăяo��
	Character::Move();

	//�A�j���[�V��������
	Texture2D* texture;
	switch (walkCnt / 10 % 4)
	{
	case 0:
		texture = TextureCache::sharedTextureCache()->addImage("Images/Phoenix_Chara.png");

		s_player->setTexture(texture);
		s_player->setContentSize(texture->getContentSize());

		break;
	case 1:
	case 3:
		texture = TextureCache::sharedTextureCache()->addImage("Images/Phoenix_Chara2.png");

		s_player->setTexture(texture);
		s_player->setContentSize(texture->getContentSize());
		break;
	case 2:
		texture = TextureCache::sharedTextureCache()->addImage("Images/Phoenix_Chara3.png");

		s_player->setTexture(texture);
		s_player->setContentSize(texture->getContentSize());
		break;
	}
}
