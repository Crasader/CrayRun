/***************************************************************************
*|
*|	�T�v�@�X�R�A�N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��,GS2 24 �R�{�I��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "Rabbit.h"


USING_NS_CC;
using namespace cocos2d::experimental;



bool Rabbit::init()
{
	if (!Character::init())
	{

		return false;
	}

	GameManager::ScoreCorrection = 1.0f;
	// ���ʂ̉摜����ύX
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/Rabbit_Chara.png");

	s_player->setTexture(texture);
	s_player->setContentSize(texture->getContentSize());

	return true;
}

void Rabbit::Jump()
{
	//JumpBy* jumpaction = JumpBy::create(0.5f, Vec2(0,0), 64.0f, 1);
	//s_player->runAction(jumpaction);
	GameManager::JumpCnt++;

	if (GameManager::JumpFlag == true)
	{
		GameManager::PlayerSpd.y = 18.0f;
	}

	if (GameManager::JumpCnt == 2)
	{
		GameManager::JumpCnt = 0;
		GameManager::JumpFlag = false;
	}
}