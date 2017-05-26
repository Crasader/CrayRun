/***************************************************************************
*|
*|	概要　スコアクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "Background.h"
#include "../../GameManager.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;


bool Background::init()
{
	if (!Node::init()) {

		return false;
	}

	sizeX = 960;

	/*background = Sprite::create("Images/PlayBackground.png");
	background->setPosition(Vec2(GameManager::m_cameraposx, 320 + GameManager::m_cameraspdx));
	this->addChild(background);

	background = Sprite::create("Images/PlayBackground.png");
	background->setPosition(Vec2(GameManager::m_cameraposx + sizeX, 320 + GameManager::m_cameraspdx));
	this->addChild(background);*/

	return true;
}

void Background::update(float delta)
{
	if (static_cast<int>(GameManager::m_cameraposx - 480) % sizeX == 0)
	{
		/*background = Sprite::create("Images/PlayBackground.png");
		background->setPosition(Vec2(GameManager::m_cameraposx + 960, 320 + GameManager::m_cameraspdx));
		this->addChild(background);*/
	}

}


