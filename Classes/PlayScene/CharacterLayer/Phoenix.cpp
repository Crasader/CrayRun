#include "Phoenix.h"

/* ---- –¼‘O‹óŠÔ‚ð‰ð•ú -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

bool Phoenix::init()
{
	if (!Character::init())
	{
		return false;
	}
	GameManager::ScoreCorrection = 1.3f;
	// •’Ê‚Ì‰æ‘œ‚©‚ç•ÏX
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/Phoenix_Chara.png");

	s_player->setTexture(texture);
	s_player->setContentSize(texture->getContentSize());

	JumpSize = 9.0f;
	return true;
}
