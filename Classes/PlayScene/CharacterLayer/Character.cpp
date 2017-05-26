/***************************************************************************
*|
*|	�T�v�@�L�����N�^�N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��,GS2 24 �R�{�I��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "Character.h"

#include "audio/include//AudioEngine.h"



/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
using namespace experimental;


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

	//�v���C�����ő�̑傫������Ȃ��Ƃ�true�ɁA�ő�̑傫���Ȃ�false
	if (GameManager::PlayerSize.x < PLAYER_MAX_SIZE && GameManager::PlayerSize.y < PLAYER_MAX_SIZE)
	{
		isScale = true;
	}
	else 
	{
		isScale = false;
	}
		
	walkCnt = 0;

	JumpSize = 11.0f;
	FloormultipleFlag = false;
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

	walkCnt++;
	Animation();
}

/***************************************************************************
*|	�T�v�@  �W�����v
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void Character::Jump()
{
	//�W�����v�����񐔂��C���N�������g
	JumpCnt++;

	//�W�����v�\�Ȃ�W�����v������
	if (JumpFlag == true)
	{
		//�W�����v���Đ�
		AudioEngine::play2d("Sounds/jump04.mp3");
		GameManager::PlayerSpd.y = JumpSize;
	}
	//���W�����v������W�����v�s�ɂ���
	if (JumpCnt == 2)
	{
		JumpCnt = 0;
		JumpFlag = false;
	}
}

void Character::Animation()
{
	Texture2D* texture;
	
	//�W�����v�ł���Ƃ����W�����v���܂����Ă��Ȃ��Ƃ��i�����Ă�Ƃ��j
	if (JumpCnt == 0 && JumpFlag == true)
	{
		switch (walkCnt / AnimationSpd % 4)
		{
		case 0:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Player2.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());

			break;
		case 1:
		case 3:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Player_w.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());

			break;
		case 2:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Player_w2.png");

			s_player->setTexture(texture);
			s_player->setContentSize(texture->getContentSize());

			break;
		}
	}
	else
	{
		texture = TextureCache::sharedTextureCache()->addImage("Images/Player_j.png");

		s_player->setTexture(texture);
		s_player->setContentSize(texture->getContentSize());
	}
}

/***************************************************************************
*|	�T�v�@  �X�P�[���̐ݒ�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void Character::setScale()
{

	if (FloormultipleFlag == false)
	{
		//�v���C���[�̃T�C�YX���ʏ��菬�����Ƃ�
		if (GameManager::PlayerSize.x < PLAYER_MAX_SIZE)
		{
			//�������傫������
			GameManager::PlayerSize.x += 0.15f;
		}
		else if (GameManager::PlayerSize.x > PLAYER_MAX_SIZE)
		{
			GameManager::PlayerSize.x = PLAYER_MAX_SIZE;

		}

		//�v���C���[�̃T�C�YY���ʏ��菬�����Ƃ�
		if (GameManager::PlayerSize.y < PLAYER_MAX_SIZE)
		{
			GameManager::PlayerSize.y += 0.35f;
		}
		else if (GameManager::PlayerSize.y > PLAYER_MAX_SIZE)
		{
			GameManager::PlayerSize.y = PLAYER_MAX_SIZE;
		}

		if (GameManager::PlayerSize.x == PLAYER_MAX_SIZE && GameManager::PlayerSize.y == PLAYER_MAX_SIZE)
		{
			isScale = false;
		}

		//�T�C�Y��K�p����
		s_player->setScale(GameManager::PlayerSize.x / PLAYER_MAX_SIZE, GameManager::PlayerSize.y / PLAYER_MAX_SIZE);
	}
}