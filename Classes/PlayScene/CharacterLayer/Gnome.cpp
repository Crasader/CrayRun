/***************************************************************************
*|
*|	概要　　ノームクラスを定義する
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/6/1
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "Gnome.h"
/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool Gnome::init()
{
	if (!Character::init())
	{
		return false;
	}
	GameManager::ScoreCorrection = SCORECORRECTION;
	// 普通の画像から変更
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/Gnome_Chara.png");

	s_player->setTexture(texture);
	s_player->setContentSize(texture->getContentSize());

	JumpSize = JUMPSIZE;
	return true;
}

/// <summary>
/// アニメーションする関数（継承）
/// </summary>


void Gnome::Animation()
{
	//アニメーションする
	Texture2D* texture;
	//ジャンプできるときかつジャンプをまだしていないとき（歩いてるとき）
	if (GameManager::JumpCnt == 0 && GameManager::JumpFlag == true)
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
