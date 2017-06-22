/***************************************************************************
*|
*|	�T�v�@�R�C���N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  �C���N���[�h ---------- */
#include "NeedleSprite.h"
/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
using namespace std;
/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@�摜��
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool NeedleSprite::init(std::string filename)
{
	if (!Sprite::initWithFile(filename)) {

		return false;
	}
	
	m_state = true;

	//���t���[���Ă�
	this->scheduleUpdate();

	return true;
}


/***************************************************************************
*|	�T�v�@�@�X�v���C�g���쐬����B
*|	�����@	�摜��
*|�@�߂�l�@�V�[���̃A�h���X
****************************************************************************/
NeedleSprite* NeedleSprite::create(string filename)
{
	//�������m��
	NeedleSprite *pRet = new(nothrow)NeedleSprite();

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
*|	�T�v�@�@�}���`�^�b�`����B
*|	�����@	�^�b�`���W
*|�@�߂�l�@����
****************************************************************************/

void NeedleSprite::MultiTouchColliosion(cocos2d::Vec2 touchpos)
{
	//�L���ȃ^�b�`�̐�
	const int EFFECTIVENESSTOUCH = 2;

	////�^�b�`��������������
	GameManager::Direction m_touch_collision_direction[EFFECTIVENESSTOUCH];
	//�^�b�`���L�����N�^�[�ɓ���������
	bool m_touch_collision[2];




	//�^�b�`���v���C���[�ɓ���������
	m_touch_collision[0] = GameManager::HitJudgment(
		touchpos - Vec2(GameManager::TOUCH_SIZE.x / 2, -GameManager::TOUCH_SIZE.y / 2), GameManager::TOUCH_SIZE,
		getPosition() + Vec2(MAX_SIZE.x / 2, -MAX_SIZE.y / 2), MAX_SIZE);
	//�^�b�`2���v���C���[�ɓ���������
	m_touch_collision[1] = GameManager::HitJudgment(
		*(&touchpos + 1) - Vec2(GameManager::TOUCH_SIZE.x / 2, -GameManager::TOUCH_SIZE.y / 2), GameManager::TOUCH_SIZE,
		getPosition() + Vec2(MAX_SIZE.x / 2, -MAX_SIZE.y / 2), MAX_SIZE);

	//�^�b�`����Ƃ��v���C���[�ɓ���������
	if (m_touch_collision[0] == true && m_touch_collision[1] == true)
	{
		// ���ʂ̉摜����ύX
		Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/needle2.png");
		setTexture(texture);
		m_state = false;
	}
}

/***************************************************************************
*|	�T�v�@  �j�ƃv���C���̓����蔻��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void NeedleSprite::CollisionPlayer()
{

		//�j���Ƃ����Ă��邩
		if (m_state == true)
		{
			if (GameManager::HitJudgment(this->getPosition() + Vec2(-GameManager::LAYRE_SIZE.x / 2, GameManager::LAYRE_SIZE.y / 2),
				GameManager::LAYRE_SIZE, GameManager::PlayerPos, GameManager::PlayerSize) == true)
			{
				if (GameManager::Mold != GameManager::Normal)
				{
					GameManager::InvincibleFlag = true;
				}
				else
				{
					//���G��ԂłȂ���
					if (GameManager::InvincibleFlag != true)
					{
						//	�Q�[���I�[�o�[�ɂ���
						GameManager::GameOverFlag = true;
					}
				}
			
				
			}
		}
}



void NeedleSprite::update(float data)
{
	
	//�v���C���[�Ƃ̏Փ˔���
	CollisionPlayer();
	
}

