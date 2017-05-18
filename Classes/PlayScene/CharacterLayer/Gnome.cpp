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

	JumpSize = 8.0f;
	return true;
}
