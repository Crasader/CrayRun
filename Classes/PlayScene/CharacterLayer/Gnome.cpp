#include "Gnome.h"

/* ---- –¼‘O‹óŠÔ‚ð‰ð•ú -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

bool Gnome::init()
{
	if (!Character::init())
	{
		return false;
	}
	GameManager::ScoreCorrection = 1.2f;
	// •’Ê‚Ì‰æ‘œ‚©‚ç•ÏX
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/Gnome_Chara.png");

	s_player->setTexture(texture);
	s_player->setContentSize(texture->getContentSize());

	JumpSize = 8.0f;
	return true;
}
