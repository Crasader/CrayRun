#include "GameManager.h"

USING_NS_CC;
//�v���C�V�[��

const  int GameManager::BOX_COLLIDER = 10;			//�����蔻�莞�Ɏg�p����^�C�����C���[�̕����班�����������ɓ����Ă��邩�m���߂邽�߂̐�
const  int GameManager::BOX_COLLIDER2 = 40;			//�����蔻�莞�Ɏg�p����^�C�����C���[�̕����班�����������ɓ����Ă��邩�m���߂邽�߂̐�

float GameManager::WorldPosX = 0.0f;

//////////////�L�����N�^�[���C���[//////
//////////////�L�����N�^�[//////////////
Vec2 GameManager::PlayerSpd = (Vec2(6.0f,-4.0f));//���x
Vec2  GameManager::PlayerSize = Vec2(96, 96);//�T�C�Y
Vec2  GameManager::PlayerPos = Vec2(300.0f,300.0f);//���W
float  GameManager::ScoreCorrection = 1.0f;//�X�R�A�␳
bool GameManager::RightFlag = false;//�E���ɓ���������

int GameManager::FirstTouchCnt = 0;//�ŏ��̃^�b�`����ǂꂾ���o�߂�����
bool GameManager::FirstTouchFlag = false;//�ŏ��̃^�b�`���Ă΂ꂽ��
int GameManager::PlayerMapPos = 0;//���Ԗڂ̍��W�ɂ��邩


///////////////�X�e�[�W���C���[/////////
std::vector<cocos2d::TMXTiledMap*>  GameManager::map;//�}�b�v

const Vec2 GameManager::MAP_SIZE = Vec2(960 * 2, 640);//�}�b�v�傫��
const Vec2 GameManager::LAYRE_SIZE = Vec2(64,64);//���C���[�̑傫��
int  GameManager::MapLoopCnt = 0;//�X�e�[�W�����[�v��������
std::vector<std::vector<Vec2>> GameManager::AllFloorPos;//�����W

//////////////�Ζ�////////////////////
int  GameManager::SlopeCnt = 0;//�ΖʃJ�E���g
std::vector<std::vector<Vec2>> GameManager::AllLeftPos;
std::vector<std::vector<Vec2>> GameManager::AllRightPos;


///////////////��/////////////////////
float GameManager::SlopePosY = 0.0f;//�Ζʍ��WY

/////////////�S�y�X�e�[�W////////
std::vector<std::vector<cocos2d::Vec2>>  GameManager::AllCrayFloorPos;//�S�y�����W
const Vec2   GameManager::MAX_CRAYSTAGESIZE = Vec2(192, 320);////�S�y���̍ő�T�C�Y

std::vector<Vec2>   GameManager::CrayFloorSize;//�S�y���̑傫��
int GameManager::CraySizeChangeCnt = 0;//�ǂ̔S�y���̃T�C�Y��ύX���邩
bool GameManager::CraySizeChangeFlag = false;//�S�y���̃T�C�Y�ύX���邩


//////////////�R�C��//////////////
std::vector<int>  GameManager::CoinPoint;//�R�C���̃|�C���g
std::vector<std::vector<Vec2>> AllLeftPos;//�S�Ă̎Ζʍ��[�̍��W
std::vector<std::vector<Vec2>> AllRightPos;//�S�Ă̎ΖʉE�[�̍��W

/////////////���^////////////////

int GameManager::Mold = 0;//���^
bool GameManager::ChangeMold = false;//���^�ω����邩

int GameManager::MoldCnt = 0;

std::vector<cocos2d::Vec2> GameManager::MoldPos;//���^�̍��W

Vec2 GameManager::MoldSpd = Vec2(0, -4);
/////////////////UI���C���[/////////////////
/////////////////�X�R�A////////////////
int GameManager::Score = 0;//�X�R�A
/////////////////�ꏊ////////////////////////
int GameManager::SaveDistance = 0;//������ۑ�����


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
*|	�T�v�@�@�Փ˔��蔻��
*|	�����@�@�I�u�W�F�N�g���W,�I�u�W�F�N�g�T�C�Y,�v���C���[���W,�I�u�W�F�N�g�T�C�Y
*|�@�߂�l�@0:��	1:�}�b�v���C���[�̏�ɏ����	2:�}�b�v���C���[�̉E���ɓ�������
*************************************************************************************/
Direction  GameManager::CollisionDetermination2(Vec2 Apos, Vec2 Asize, Vec2 Bpos, Vec2 Bsize)
{
	//�}�b�v���C���[�̏�ɏ������
	if (Apos.x <= Bpos.x + Bsize.x / 2)
	{
		if (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		{
			if (Apos.y >= Bpos.y)
			{
				if (Apos.y - GameManager::BOX_COLLIDER2 <= Bpos.y)
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
				if (Apos.y - Asize.y + GameManager::BOX_COLLIDER2 >= Bpos.y + Bsize.y)
				{
					{
						return under;
					}
				}
			}
		}
	}

	//�}�b�v���C���[�̍����ɓ���������
	if (Apos.x + GameManager::BOX_COLLIDER2 >= Bpos.x + Bsize.x / 2)
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
	if (Apos.x + Asize.x - GameManager::BOX_COLLIDER2 <= Bpos.x - Bsize.x / 2)
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


