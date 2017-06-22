/***************************************************************************
*|
*|	概要　　魔法使いクラスを定義する
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/6/2
*|___________________________________________________________________________
****************************************************************************/


/* ----  インクルード ---------- */
#include "Witch.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool Witch::init()
{
	if (!Character::init())
	{

		return false;
	}
	//スコアの倍率を設定
	GameManager::ScoreCorrection = SCORECORRECTION;
	// 普通の画像から変更
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Images/Witch1.png");

	s_player->setTexture(texture);
	s_player->setContentSize(texture->getContentSize());

	JumpSize = JUMPSIZE;

	return true;
}

void Witch::Animation()
{
	Texture2D* texture;

	//ジャンプできるときかつジャンプをまだしていないとき（歩いてるとき）
	if (GameManager::JumpCnt == 0 && GameManager::JumpFlag == true)
	{
		
		std::ostringstream ImaseName;
		int ImageNumber = walkCnt / 7 % 4 + 1;

		ImaseName << "Images/Witch" << ImageNumber << ".png";
		
		texture = Director::getInstance()->getTextureCache()->addImage(ImaseName.str());
		s_player->setTexture(texture);
		s_player->setContentSize(texture->getContentSize());
	}
	else {
		texture = Director::getInstance()->getTextureCache()->addImage("Images/WitchJ.png");
		s_player->setTexture(texture);
		s_player->setContentSize(texture->getContentSize());
	}
}
