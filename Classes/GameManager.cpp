#include "GameManager.h"

USING_NS_CC;

//////////////�L�����N�^�[���C���[//////
//////////////�L�����N�^�[//////////////
Vec2 GameManager::PlayerSpd = (Vec2(3.0f,0.0f));//���x
Vec2  GameManager::PlayerSize = Vec2(64, 64);//�T�C�Y
Vec2  GameManager::PlayerPos = Vec2(300.0f,300.0f);//���W
float  GameManager::ScoreCorrection = 0.0f;//�X�R�A�␳
bool GameManager::GroundFlag = false;//�n�ʂɂ��Ă��邩

///////////////�X�e�[�W���C���[/////////
//struct GameManager::SlopePos
//{
//	Vec2 LeftEnd;//���[
//	Vec2 RightEnd;//�E�[
//};
float GameManager::SlopePosY = 0.0f;//�Ζʍ��WY
bool GameManager::SlopeFalg = false;


int GameManager::ScoreMaxDigit = 0;//�ő包��
int GameManager::DistanceMaxDigit = 0;//�ő包��
int GameManager::Digit = 0;//����
int GameManager::SaveDistance = 0;//������ۑ�����
int GameManager::SaveScore = 0;//�X�R�A��ۑ�����
int GameManager::SpriteCnt = 0;//���ڂ̃X�v���C�g���J�E���g����
bool GameManager::UsedFlag = false;//���̊֐������łɌĂ΂ꂽ��

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

/************************************************************************************
*|	�T�v�@�@�Փ˔��蔻��
*|	�����@�@�I�u�W�F�N�g���W,�I�u�W�F�N�g�T�C�Y,�v���C���[���W,�I�u�W�F�N�g�T�C�Y
*|�@�߂�l�@0:��	1:�}�b�v���C���[�̏�ɏ����	2:�}�b�v���C���[�̉E���ɓ�������
*************************************************************************************/
int  GameManager::CollisionDetermination(Vec2 Apos,Vec2 Asize, Vec2 Bpos,Vec2 Bsize)
{
	//�}�b�v���C���[�̏�ɏ������
	if (Apos.x <= Bpos.x + Bsize.x / 2)
	{
		if (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		{
			if (Apos.y >= Bpos.y)
			{
				if (Apos.y - GameManager::PlayerSpd.y <= Bpos.y)
				{
					{
						return up;
					}
				}
			}
		}
	}

	//�}�b�v���C���[�̉��ɏ������
	if (Apos.x <= Bpos.x + Bsize.x / 2)
	{
		if (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		{
			if (Apos.y - Asize.y <= Bpos.y + Bsize.y)
			{
				if (Apos.y - Asize.y + GameManager::PlayerSpd.y >= Bpos.y + Bsize.y)
				{
					{
						return under;
					}
				}
			}
		}
	}

	//�}�b�v���C���[�̍����ɓ���������
	if (Apos.x + GameManager::PlayerSpd.y >= Bpos.x + Bsize.x / 2)
	{
		if (Apos.x <= Bpos.x + Bsize.x / 2)
		{
			if (Apos.y >= Bpos.y)
			{
				if (Apos.y - Asize.y <= Bpos.y + Bsize.y)
				{
					{
						return left;
					}
				}
			}
		}
	}


	//�}�b�v���C���[�̉E���ɓ���������
	if (Apos.x + Asize.x - GameManager::PlayerSpd.y <= Bpos.x - Bsize.x / 2)
	{
		if (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		{
			if (Apos.y >= Bpos.y)
			{
				if (Apos.y - Asize.y <= Bpos.y + Bsize.y)
				{
					{
						return right;
					}
				}
			}
		}
	}



	//���ɂ��������Ă��Ȃ�
	return exception;
}


/************************************************************************************
*|	�T�v�@�@�Փ˔���(�Ε�)
*|	�����@�@�ΕӍ��[���W,�ΕӉE�[���W,�I�u�W�F�N�g���W
*|�@�߂�l�@true���������@false �������ĂȂ�
*************************************************************************************/
int GameManager::DiagonalCollisionDetermination(Vec2 Apos, Vec2 Bpos, Vec2 Object) {

	Vec2 v;
	Vec2 A;
	Vec2 B;
	float w;
	float d;
	bool direction;

	//�L�����N�^�[�̒��S�����߂�
	Object.y += GameManager::PlayerSize.y;
	//Object.y -= GameManager::PlayerSize.y / 2;

	v = Bpos - Apos;
	A = Object - Apos;
	B = Object - Bpos;

	//Apos��Bpos�̋���
	w = Apos.distance(Bpos);
	//
	d = v.cross(A) / w;

	//�}�C�i�X�̎�
	if (d < 0)
	{
		//�����ɕς���
		d *= -1.0f;
		direction = false;
	}
	else
	{
		direction = true;
	}


	if (d <= PlayerSize.y)
	{
		if (A.dot(v) * B.dot(v) <= 0)
		{
			if (direction == true)
			{
				GameManager::SlopePosY =  v.y /  v.x  * Object.x + Apos.y - GameManager::PlayerSize.y / 2;
				return up;
			}
			else
			{
				GameManager::SlopePosY = v.y / v.x  * Object.x + Apos.y - GameManager::PlayerSize.y * 2;
				return under;
			}
		}
	}

	//���ɂ��������Ă��Ȃ�
	return exception;

}

/************************************************************************************
*|	�T�v�@�@�����蔻��
*|	�����@�@�Ώۓ�̍��W
*|�@�߂�l�@true���������@false �������ĂȂ�
*************************************************************************************/
bool GameManager::HitJudgment(Vec2 Apos, Vec2 Asize, Vec2 Bpos, Vec2 Bsize)
{

	if ((Apos.x <= Bpos.x + Bsize.x / 2)
		|| (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		|| (Apos.y >= Bpos.y)
		|| (Apos.y - Asize.y <= Bpos.y + Bsize.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}


