/***************************************************************************
*|
*|	�T�v�@�X�R�A�N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "Stage.h"


USING_NS_CC;
using namespace cocos2d::experimental;



bool Stage::init()
{
	if (!Node::init()) {

		return false;

	}


		s_Sorp = Sprite::create("Images/c.png");
		s_Sorp->setAnchorPoint(Vec2(0, 0));
		s_Sorp->setPosition(Vec2(200, 200));

		this->addChild(s_Sorp);
	return true;
}


