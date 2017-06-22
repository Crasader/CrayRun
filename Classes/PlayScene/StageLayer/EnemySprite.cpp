/***************************************************************************
*|
*|	�T�v�@�G�X�v���C�g�N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  �C���N���[�h ---------- */
#include "NeedleSprite.h"
#include "EnemySprite.h"
#include "audio/include/AudioEngine.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
using namespace std;
using namespace experimental;
/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@�摜��
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool EnemySprite::init(std::string filename)
{
	if (!Sprite::initWithFile(filename)) {

		return false;
	}
	//���t���[���Ă�
	this->scheduleUpdate();

	//������
	m_animation_cnt = 0;
	return true;
}


/***************************************************************************
*|	�T�v�@�@�X�v���C�g���쐬����B
*|	�����@	�摜��
*|�@�߂�l�@�V�[���̃A�h���X
****************************************************************************/
EnemySprite* EnemySprite::create(string filename)
{
	//�������m��
	EnemySprite *pRet = new(nothrow)EnemySprite();

	if (pRet && pRet->init(filename))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}

}






/***************************************************************************
*|	�T�v�@�@���t���[���Ă΂��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void EnemySprite::update(float delta)
{
	//�A�j���[�V����
	Animation();
	//�v���C���ɓ������Ă��邩
	CollisionPlayer();
}


/***************************************************************************
*|	�T�v�@  �G�ƃv���C���̓����蔻��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void EnemySprite::CollisionPlayer()
{
		switch (GameManager::CollisionDetermination
		(this->getPosition(), GameManager::LAYRE_SIZE,
			GameManager::PlayerPos, GameManager::PlayerSize))
		{
		case GameManager::right:
			//if (GameManager::Mold != GameManager::Phoenix) {
			//	GameManager::PlayerPos.x = getPosition() .x + GameManager::LAYRE_SIZE.x + GameManager::PlayerSize.x / 2 + 1;
			//	GameManager::PlayerSpd.x = 0.0f;
			//	GameManager::InvincibleFlag = true;
			//}
			break;
		case GameManager::left:
			//�t�F�j�b�N�X�łȂ������G��ԂłȂ���
			if (GameManager::Mold != GameManager::Phoenix ) {
				/*GameManager::PlayerPos.x = GameManager::AllFloorPosx[i] - GameManager::PlayerSize.x / 2;*/
				//GameManager::RightFlag = true;
				//GameManager::PlayerSpd.x = -6.0f;
				if (GameManager::InvincibleFlag == false)
				{
					//�h�[���N�̈ȊO��
					if (GameManager::Mold != GameManager::Normal)
					{
						//�M�~�b�N�ɓ��������Ƃ��ăQ�[���I�[�o�[
						GameManager::InvincibleFlag = true;
					}
					else
					{
						//�Q�[���I�[�o�[
						GameManager::GameOverFlag = true;
					}
				}
				
			}
			
	
		


			break;
		case GameManager::up:
			GameManager::PlayerPos.y = getPosition().y;
			
			//�W�����v�\�ɂ���
			GameManager::JumpCnt = 0;
			GameManager::JumpFlag = true;

			
			//�W�����v�\�Ȃ�W�����v������
			if (GameManager::JumpFlag == true)
			{
				//�W�����v���Đ�
				AudioEngine::play2d("Sounds/jump04.ogg");
				GameManager::PlayerSpd.y = 10;
			}

			////���W�����v������W�����v�s�ɂ���
			//if (GameManager::JumpCnt == 2)
			///*if (GameManager::Mold != GameManager::Phoenix) */{
			//	GameManager::PlayerPos.y = this->getPosition().y - GameManager::LAYRE_SIZE.y - GameManager::PlayerSize.y;
			//	GameManager::PlayerSpd.y = 0.0f;
			//}
			break;
		default:
			break;
	}
}



/***************************************************************************
*|	�T�v�@�@�A�j���[�V����
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void EnemySprite::Animation()
{
	if (m_animation_cnt % 7 == 0)
	{
		Texture2D* texture;
		switch (m_animation_cnt / 7 % 6)
		{
		case 0:
		case 5:
			texture = TextureCache::sharedTextureCache()->addImage("Images/enemy1.png");
			this->setTexture(texture);
			break;
		case 1:
		case 4:
			texture = TextureCache::sharedTextureCache()->addImage("Images/enemy3.png");
			this->setTexture(texture);
			break;
		case 2:
		case 3:
			texture = TextureCache::sharedTextureCache()->addImage("Images/enemy2.png");

			this->setTexture(texture);
			break;
		default:
			break;
		}
	}
	m_animation_cnt++;
}

