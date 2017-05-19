/***************************************************************************
*|
*|	�T�v�@�L�����N�^�N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��,GS2 24 �R�{�I��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "Character.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;



bool Character::init()
{
	if (!Node::init()) {

		return false;
	}



	if (s_player == nullptr){
		//�v���C���[�쐬
		s_player = Sprite::create("Images/Player2.png");
		s_player->setPosition(GameManager::PlayerPos);
		s_player->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(s_player);
	}
	else {
		Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/Player2.png");

	}

	isScaleX = false;
	isScaleY = false;

	JumpSize = 9.0f;
		
	return true;
}

/***************************************************************************
*|	�T�v�@�@�ړ�����
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void Character::Move()
{
	//���W�ɑ��x������
	GameManager::PlayerPos += GameManager::PlayerSpd;
	//���W��K�p������
	s_player->setPosition(GameManager::PlayerPos);
}

/***************************************************************************
*|	�T�v�@  �W�����v
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void Character::Jump()
{

	//�W�����v�����񐔂��C���N�������g
	GameManager::JumpCnt++;

	//�W�����v�\�Ȃ�W�����v������
	if (GameManager::JumpFlag == true)
	{
		GameManager::PlayerSpd.y = JumpSize;
	}
	//���W�����v������W�����v���ׂɂ���
	if (GameManager::JumpCnt == 2)
	{
		GameManager::JumpCnt = 0;
		GameManager::JumpFlag = false;
	}
}

/***************************************************************************
*|	�T�v�@  �X�P�[���̐ݒ�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void Character::setScale()
{

	//�v���C���[�̃T�C�YX���ʏ��菬�����Ƃ�
	if (GameManager::PlayerSize.x < PLAYER_MAX_SIZE)
	{
		//�������傫������
		GameManager::PlayerSize.x += 0.1f;
	}
	else if (GameManager::PlayerSize.x > PLAYER_MAX_SIZE)
	{
		GameManager::PlayerSize.x = 96;
	}

	//�v���C���[�̃T�C�YY���ʏ��菬�����Ƃ�
	if (GameManager::PlayerSize.y < PLAYER_MAX_SIZE)
	{
		GameManager::PlayerSize.y += 0.1f;
	}
	else if (GameManager::PlayerSize.y > PLAYER_MAX_SIZE)
	{
		GameManager::PlayerSize.y = 96;
	}

	if (GameManager::PlayerSize.x == PLAYER_MAX_SIZE)
	{
		isScaleX = false;
	}
	if (GameManager::PlayerSize.y == PLAYER_MAX_SIZE)
	{
		isScaleY = false;
	}

	//�T�C�Y��K�p����
	s_player->setScale(GameManager::PlayerSize.x / PLAYER_MAX_SIZE, GameManager::PlayerSize.y / PLAYER_MAX_SIZE);
}