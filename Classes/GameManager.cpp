#include "GameManager.h"

USING_NS_CC;

//�v���C�V�[��

const  int GameManager::BOX_COLLIDER = 10;			//�����蔻�莞�Ɏg�p����^�C�����C���[�̕����班�����������ɓ����Ă��邩�m���߂邽�߂̐�


//////////////�L�����N�^�[���C���[//////
//////////////�L�����N�^�[//////////////
Vec2 GameManager::PlayerSpd = (Vec2(6.0f,-4.0f));//���x
Vec2  GameManager::PlayerSize = Vec2(64, 64);//�T�C�Y
Vec2  GameManager::PlayerPos = Vec2(50.0f,300.0f);//���W
float  GameManager::ScoreCorrection = 0.0f;//�X�R�A�␳
bool GameManager::JumpFlag = false;//�n�ʂɂ��Ă��邩
bool GameManager::RightFlag = false;//�E���ɓ���������
int  GameManager::JumpCnt = 0;//�W�����v�t���O


int GameManager::FirstTouchCnt = 0;//�ŏ��̃^�b�`����ǂꂾ���o�߂�����
bool GameManager::FirstTouchFlag = false;//�ŏ��̃^�b�`���Ă΂ꂽ��

///////////////�X�e�[�W���C���[/////////
TMXTiledMap*  GameManager::map = nullptr;//�}�b�v
const Vec2 GameManager::MAP_SIZE = Vec2(960 * 2, 640);//�}�b�v�傫��
const Vec2 GameManager::LAYRE_SIZE = Vec2(64,64);//���C���[�̑傫��
std::vector<Vec2> GameManager::FloorPos;//�����W


//�Ζ�

std::vector<Vec2> GameManager::LeftPos;//���[
std::vector<Vec2> GameManager::RightPos;//�E�[

										//�C�e���[�^�̒l���i�[����
cocos2d::Vec2 GameManager::SaveRight;
cocos2d::Vec2 GameManager::SaveLeft;

///////////////��/////////////////////
float GameManager::SlopePosY = 0.0f;//�Ζʍ��WY
//////////////�R�C��//////////////

int  GameManager::CoinCnt = 0;//�R�C�����J�E���g
std::vector<int>  GameManager::CoinPoint;//�R�C���̃|�C���g


/////////////////UI���C���[/////////////////
/////////////////�X�R�A////////////////
std::vector<cocos2d::Sprite*> GameManager::s_score;//�R�C��
int GameManager::ScoreMaxDigit = 0;//�ő包��
int GameManager::Score = 0;//�X�R�A
int GameManager::SaveScore = 0;//�X�R�A��ۑ�����
/////////////////�ꏊ////////////////////////
int GameManager::DistanceMaxDigit = 0;//�ő包��
int GameManager::Digit = 0;//����
int GameManager::Distance = 0;//����

int GameManager::SaveDistance = 0;//������ۑ�����
int GameManager::SpriteCnt = 0;//���ڂ̃X�v���C�g���J�E���g����
bool GameManager::UsedFlag = false;//���̊֐������łɌĂ΂ꂽ��


/////////////////�J����//////////////////////.
float GameManager::m_cameraposx = 480.0f;
const float GameManager::m_cameraspdx = GameManager::PlayerSpd.x;

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
Direction  GameManager::CollisionDetermination(Vec2 Apos,Vec2 Asize, Vec2 Bpos,Vec2 Bsize)
{
	//�}�b�v���C���[�̏�ɏ������
	if (Apos.x <= Bpos.x + Bsize.x / 2)
	{
		if (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		{
			if (Apos.y >= Bpos.y)
			{
				if (Apos.y - GameManager::BOX_COLLIDER <= Bpos.y)
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
				if (Apos.y - Asize.y + GameManager::BOX_COLLIDER >= Bpos.y + Bsize.y)
				{
					{
						return under;
					}
				}
			}
		}
	}

	//�}�b�v���C���[�̍����ɓ���������
	if (Apos.x + GameManager::BOX_COLLIDER >= Bpos.x + Bsize.x / 2)
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
	if (Apos.x + Asize.x - GameManager::BOX_COLLIDER <= Bpos.x - Bsize.x / 2)
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
Direction GameManager::DiagonalCollisionDetermination(Vec2 Apos, Vec2 Bpos, Vec2 Object) {

	Vec2 v;
	Vec2 A;
	Vec2 B;
	float w;
	float d;
	bool direction;

	//�L�����N�^�[�̒��S�����߂�
	Object.y += GameManager::PlayerSize.y;

	v = Bpos - Apos;
	A = Object - Apos;
	B = Object - Bpos;

	//v.normalize();

	float f = v.y;

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

	//	�������Ă��邩
	if (d <= PlayerSize.y)
	{
		//��������̔�������O����
		if (A.dot(v) * B.dot(v) <= 0)
		{
			//�v���C���[���ォ�瓖�������ꍇ
			if (direction == true)
			{
				GameManager::SlopePosY = v.y / v.x  * (Object.x - Apos.x ) + Apos.y; /*- GameManager::PlayerSize.y */ 

				return up;
			}
			//�v���C���[�������瓖�������ꍇ
			else
			{
				//GameManager::SlopePosY = v.y / v.x  * Object.x + Apos.y - GameManager::PlayerSize.y * 2;
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
		&& (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		&& (Apos.y >= Bpos.y)
		&& (Apos.y - Asize.y  /2  <= Bpos.y + Bsize.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}


