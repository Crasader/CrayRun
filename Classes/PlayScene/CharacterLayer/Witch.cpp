/***************************************************************************
*|
*|	�T�v�@�@���@�g���N���X���`����
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/6/2
*|___________________________________________________________________________
****************************************************************************/


/* ----  �C���N���[�h ---------- */
#include "Witch.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@����
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool Witch::init()
{
	if (!Character::init())
	{

		return false;
	}
	//�X�R�A�̔{����ݒ�
	GameManager::ScoreCorrection = SCORECORRECTION;
	// ���ʂ̉摜����ύX
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Images/Witch1.png");

	s_player->setTexture(texture);
	s_player->setContentSize(texture->getContentSize());

	JumpSize = JUMPSIZE;

	return true;
}

void Witch::Animation()
{
	Texture2D* texture;

	//�W�����v�ł���Ƃ����W�����v���܂����Ă��Ȃ��Ƃ��i�����Ă�Ƃ��j
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
