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
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/Rabbit_Chara2.png");

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
		switch (walkCnt / 10 % 4)
		{
		case 0:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Rabbit_Chara.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());

			break;
		case 1:
		case 3:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Rabbit_Chara2.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());

			break;
		case 2:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Rabbit_Chara3.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());

			break;
		}
	}
	else
	{
		texture = TextureCache::sharedTextureCache()->addImage("Images/Rabbit_Charaj.png");

		s_player->setTexture(texture);
		s_player->setContentSize(texture->getContentSize());
	}
}
