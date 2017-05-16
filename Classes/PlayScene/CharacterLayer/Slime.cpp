/// <summary>
/// 概　要：スライムクラスの定義
/// 作成者：GS2 24 山本悠雅
/// 作成日：2017/05/15
/// </summary>

/* ---- ライブラリのインクルード ---------- */

#include "Slime.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;
bool Slime::init()
{
	if (!Character::init())
	{

		return false;
	}

	GameManager::ScoreCorrection = 5.0f;
	// 普通の画像から変更
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/1.png");

	s_player->setTexture(texture);
	s_player->setContentSize(texture->getContentSize());

	JumpSize = 10.0f;

	return true;
}
