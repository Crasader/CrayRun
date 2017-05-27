/***************************************************************************
*|
*|	概要　ウサギクラスの定義
*|　作成者　GS2 16 中田湧介,GS2 24 山本悠雅
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "Rabbit.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;



bool Rabbit::init()
{
	if (!Character::init())
	{

		return false;
	}

	GameManager::ScoreCorrection = 1.2f;
	// 普通の画像から変更
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/Rabbit2.png");

	s_player->setTexture(texture);
	s_player->setContentSize(texture->getContentSize());

	JumpSize = 13.0f;
	
	return true;
}

void Rabbit::Animation()
{
	Texture2D* texture;	
	
	//ジャンプできるときかつジャンプをまだしていないとき（歩いてるとき）
	if (JumpCnt == 0 && JumpFlag == true)
	{
		switch (walkCnt / AnimationSpd % 6)
		{
		case 0:
		case 1:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Rabbit3.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());

			break;
		case 2:
		case 3:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Rabbit1.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());

			break;
		case 4:
		case 5:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Rabbit2.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());

			break;
		}
	}
	else
	{
		texture = TextureCache::sharedTextureCache()->addImage("Images/Rabbit3.png");
		s_player->setTexture(texture);
		s_player->setContentSize(texture->getContentSize());
	}
}
