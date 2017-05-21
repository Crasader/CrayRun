#include "Gnome.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

bool Gnome::init()
{
	if (!Character::init())
	{
		return false;
	}
	GameManager::ScoreCorrection = 1.2f;
	// 普通の画像から変更
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/Gnome_Chara.png");

	s_player->setTexture(texture);
	s_player->setContentSize(texture->getContentSize());

	JumpSize = 9.0f;
	return true;
}

/// <summary>
/// 移動する関数（継承）
/// </summary>
void Gnome::Move()
{
	//基底クラスのMoveを呼び出す
	Character::Move();
	
	//アニメーションする
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
