/***************************************************************************
*|
*|	�T�v�@�ΖʃX�v���C�g�N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/6/5
*|___________________________________________________________________________
****************************************************************************/
/* ----  �C���N���[�h ---------- */
#include "SlopeSprite.h"
/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
using namespace std;
/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@�摜��,���E���_���W
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool SlopeSprite::init(std::string filename, Vec2 Leftpos, Vec2 RightPos)
{
	if (!SlopeSprite::initWithFile(filename)) {

		return false;
	}
	//���E���_���W�̏�����
	m_left_pos = Leftpos;
	m_right_pos = RightPos;
	//���t���[���Ă�
	this->scheduleUpdate();

	return true;
}


/***************************************************************************
*|	�T�v�@�@�X�v���C�g���쐬����B
*|	�����@	�摜���A���E���_���W
*|�@�߂�l�@�V�[���̃A�h���X
****************************************************************************/
SlopeSprite* SlopeSprite::create(string filename, Vec2 Leftpos, Vec2 RightPos)
{
	//�������m��
	SlopeSprite *pRet = new(nothrow)SlopeSprite();

	if (pRet && pRet->init(filename, Leftpos, RightPos))
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
*|	�T�v�@  �Ζʂƃv���C���̓����蔻��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void SlopeSprite::CollisionPlayer()
{

		//�Փ˔���i�Ζʁj
		GameManager::Direction HitFlag = 
		GameManager::DiagonalCollisionDetermination(m_left_pos, m_right_pos, GameManager::PlayerPos);
		//��ɏ������
		if (HitFlag == GameManager::up)
		{
			if (!GameManager::JumpState)
			{
				GameManager::PlayerSpd.y = 0.0f;
				//���܂������������o��
				GameManager::PlayerPos.y = GameManager::SlopePosY;				//�W�����v�\�ɂ���
				GameManager::JumpCnt = 0;
				GameManager::JumpFlag = true;
;
			}


		}

			
}



void SlopeSprite::update(float data)
{

	//�v���C���[�Ƃ̏Փ˔���
	CollisionPlayer();


}

