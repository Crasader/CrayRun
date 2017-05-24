#include "Phoenix.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

bool Phoenix::init()
{
	if (!Character::init())
	{
		return false;
	}
	GameManager::ScoreCorrection = 1.3f;
	// 普通の画像から変更
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/Phoenix_Chara.png");

	s_player->setTexture(texture);
	s_player->setContentSize(texture->getContentSize());

	JumpSize = 11.0f;
	return true;
}

void Phoenix::Animation()
{
		//アニメーションする
		Texture2D* texture;
	//ジャンプできるときかつジャンプをまだしていないとき（歩いてるとき）
	if (JumpCnt == 0 && JumpFlag == true)
	{
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
	else {
		texture = TextureCache::sharedTextureCache()->addImage("Images/Phoenix_Charaj.png");

		s_player->setTexture(texture);
		s_player->setContentSize(texture->getContentSize());
	}
}
