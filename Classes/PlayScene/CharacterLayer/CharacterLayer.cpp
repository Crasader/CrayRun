/***************************************************************************
*|
*|	�T�v�@�@���U���g���C���[
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "CharacterLayer.h"

USING_NS_CC;

bool CharacterLayer::init()
{
	if (!Layer::init()) {

		return false;

	}

	//���C���[�Ƀm�[�h���W��
	character = Character::create();
	this->addChild(character);

	//���t���[���Ăяo��
	this->scheduleUpdate();

	return true;
}

/***************************************************************************
*|	�T�v�@	���t���[���Ăяo��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::update(float date)
{
	//�ړ�����
	character->Move();
	//�d��
	character->Gravity();

	//�v���C���[�ƎΖʂ̂����蔻��
	AfterHittingSlope();
}


/***************************************************************************
*|	�T�v�@	�v���C���[�ƎΖʂ̂����蔻��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::AfterHittingSlope()
{
	Vec2 a = Vec2(200, 200);
	Vec2 b = Vec2(600, 264);

	if(GameManager::DiagonalCollisionDetermination
	(a, b, GameManager::PlayerPos) == up)
	{
		GameManager::PlayerSpd.y = 0.0f;
		GameManager::PlayerPos.y = GameManager::SlopePosY/* - GameManager::PlayerSize.y / 2*/;
	}
}
