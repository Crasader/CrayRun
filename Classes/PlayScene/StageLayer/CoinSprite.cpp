/***************************************************************************
*|
*|	�T�v�@�R�C���N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  �C���N���[�h ---------- */
#include "CoinSprite.h"
#include "audio/include/AudioEngine.h"
/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;

/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@�摜���A�|�C���g
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool CoinSprite::init(std::string filename, int point)
{
	if (!Sprite::initWithFile(filename)) {

		return false;
	}

	//�X�e�[�W���C���������n�߂Ă���̃t���[������������
	FlameCnt = 0;
	//�z������邷�鋗��
	AbsorptionPos = 0.04;
	//�����Ŏ󂯎�����l���|�C���g�Ƃ��ď���������
	m_point = point;
	//���t���[���Ă�
	this->scheduleUpdate();

	return true;
}


/***************************************************************************
*|	�T�v�@�@�X�v���C�g�̍쐬
*|	�����@	�摜���A�|�C���g
*|�@�߂�l�@�V�[���̃A�h���X
****************************************************************************/
CoinSprite* CoinSprite::create(std::string filename,int point)
{
	//�������m��
	CoinSprite *pRet = new(std::nothrow)CoinSprite();

	if (pRet && pRet->init(filename,point))
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


////__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
////	�T�@�v�F���@�g���̃R�C���z�����邩�̔���
////	���@���F����
////�@�@�߂�l�F����
////__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
void CoinSprite::CollisionAbsorptionCoin()
{
	
	Vec2 a = this->getContentSize();
	//�v���C���[�ƃR�C���̓����蔻��
	if (GameManager::HitJudgment
	(this->getPosition(), this->getContentSize(),
	GameManager::PlayerPos - Vec2(0, AbsorptionSize.y/2)/* + Vec2(0.0f,GameManager::PlayerSize.y / 2)-Vec2(AbsorptionSize.x / 2 ,-AbsorptionSize.y / 2)*/, AbsorptionSize) == true)
	{
		//�z���������tosutu
		m_absorption_flag = true;
	}


}




//���@�g���ɋz������R�C������`��Ԃœ�����
void CoinSprite::AbsorptionCoin()
{
	float TimeStep;
	if (m_Move_Flag == false)
	{
		//�ړ������X�V����
		//���̎��̃t���[����ۑ�����
		FlameTime = FlameCnt;
		//�X�^�[�g���̍��W���擾����
		m_startpos = this->getPosition();
		//�i�ލ��W��ۑ�����
		m_endpos = GameManager::PlayerPos;

		//2�_�Ԃ̋������擾����
		SEdis = m_startpos.distance(m_endpos);
		//�ړ����J�n����
		m_Move_Flag = true;
	}

	//�ړ��̃t���O�����Ă���ꍇ
	if (m_Move_Flag == true)
	{
		//�ړI�n�Ɍ������Đ��`��Ԃ̏���������
		//���`��ԏ������ǂ̂��炢�V��ł��邩�������ŋ��߂�
		TimeStep = (FlameCnt - FlameTime) / ((SEdis / AbsorptionPos) + 1);

		this->setPosition(Leap(m_startpos, m_endpos, TimeStep));

		//���x������������
		AbsorptionPos += AbsorptionPos;
	}
	//���`��Ԃ͓r���ŏI�����Ĉړ��t���O���~�낷
	if (TimeStep > 0.6f)
	{
		//�ړ��I�������̂Ńt���O���~�낷
		m_Move_Flag = false;
		return;
	}

	//�X�e�[�W���C���������n�߂Ă���̃t���[�������v��
	FlameCnt++;

}

void CoinSprite::update(float data)
{
	////���@�g���Ȃ�
	if (GameManager::Mold == GameManager::Witch)
	{
		CollisionAbsorptionCoin();

		//�z�������t���O�������Ă���Ȃ�
		if (m_absorption_flag == true)
		{
			//���@�g���ɋz������R�C������`��Ԃœ�����
			AbsorptionCoin();
		}
	}

	//�R�C���̂����蔻��
	CollisionResponseCoin();
}




/***************************************************************************
*|	�T�v�@�@�R�C�������蔻��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CoinSprite::CollisionResponseCoin()
{

	//�v���C���[�ƃR�C���̓����蔻��
	if (GameManager::HitJudgment
	(this->getPosition(), this->getContentSize(),
		GameManager::PlayerPos, GameManager::PlayerSize) == true)
	{
		//�R�C���̉���true�̎��͉�
		//if (coin_Audio_flag == true)
		//{
		//	//�R�C�����Đ�
			experimental::AudioEngine::play2d("Sounds/coin03.ogg");
		//	coin_Audio_flag = false;
		//	coin_cnt = 0;
		//}

		//�X�R�A�ɂƂ����R�C���̃|�C���g������
		GameManager::Score += m_point;
		//���g���폜
		this->removeFromParent();
	
	}
		
}




	




