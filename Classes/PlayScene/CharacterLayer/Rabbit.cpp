/***************************************************************************
*|
*|	�T�v�@�E�T�M�N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��,GS2 24 �R�{�I��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "Rabbit.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;



bool Rabbit::init()
{
	if (!Character::init())
	{

		return false;
	}

	GameManager::ScoreCorrection = 1.2f;
	// ���ʂ̉摜����ύX
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/Rabbit_Chara2.png");

	s_player->setTexture(texture);
	s_player->setContentSize(texture->getContentSize());

	JumpSize = 13.0f;
	
	return true;
}

void Rabbit::Animation()
{
	Texture2D* texture;	
	
	//�W�����v�ł���Ƃ����W�����v���܂����Ă��Ȃ��Ƃ��i�����Ă�Ƃ��j
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
