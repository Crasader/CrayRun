/***************************************************************************
*|
*|	�T�v�@�X�R�A�N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "Background.h"
#include "../../GameManager.h"

/* ---- ���O��Ԃ���� -------------------- */
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


