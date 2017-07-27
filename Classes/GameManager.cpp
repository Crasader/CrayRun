#include "GameManager.h"

USING_NS_CC;

const Vec2 GameManager::LAYRE_SIZE = Vec2(64, 64);//���C���[�̑傫��

//�v���C�V�[��
float GameManager::WorldPosX = 0.0f;
bool GameManager::GameOverFlag = false;//�Q�[���I�[�o�[�t���O
bool GameManager::InvincibleFlag;//���G��Ԃ��ǂ���

const Vec2 GameManager::SCREEN_SIZE= Vec2(960,640);//��ʃT�C�Y
const Vec2 GameManager::TOUCH_SIZE = Vec2(32.0f,32.0f);	//�^�b�`�̑傫��

//////////////�L�����N�^�[���C���[//////
//////////////�L�����N�^�[//////////////
Vec2 GameManager::PlayerSpd = (Vec2(6.0f,-4.0f));//���x
Vec2  GameManager::PlayerSize = Vec2(96, 96);//�T�C�Y
Vec2  GameManager::PlayerPos = Vec2(300.0f, GameManager::LAYRE_SIZE.y * 4);//���W
int  GameManager::JumpCnt = 0;//�W�����v�����
bool  GameManager::JumpFlag = false;//�W�����v�ł��邩
bool  GameManager::JumpState = false;//�W�����v�ł��邩


float  GameManager::ScoreCorrection = 1.0f;//�X�R�A�␳


//


bool GameManager::FirstTouchFlag = false;//�ŏ��̃^�b�`���Ă΂ꂽ��
int GameManager::PlayerMapPos = 0;//���Ԗڂ̍��W�ɂ��邩


///////////////�X�e�[�W���C���[/////////
std::vector<cocos2d::TMXTiledMap*>  GameManager::map;//�}�b�v

const Vec2 GameManager::MAP_SIZE = Vec2(300 * 64, 640);//�}�b�v�傫��
int  GameManager::MapLoopCnt = 0;//�X�e�[�W�����[�v��������
std::vector<std::vector<Vec2>> GameManager::AllFloorPos;//�����W


///////////////��/////////////////////
float GameManager::SlopePosY = 0.0f;//�Ζʍ��WY

//////////////�R�C��//////////////
std::vector<std::vector<Vec2>> AllLeftPos;//�S�Ă̎Ζʍ��[�̍��W
std::vector<std::vector<Vec2>> AllRightPos;//�S�Ă̎ΖʉE�[�̍��W

/////////////���^////////////////

GameManager::CharacterKind GameManager::Mold = Normal;//���^
bool GameManager::ChangeMold = false;//���^�ω����邩

int GameManager::MoldCnt = 0;
std::vector<cocos2d::Vec2> GameManager::MoldPos;//���^�̍��W
/////////////////UI���C���[/////////////////
/////////////////�X�R�A////////////////
int GameManager::Score = 0;//�X�R�A
/////////////////�ꏊ////////////////////////
int GameManager::SaveDistance = 0;//������ۑ�����
int GameManager::TotalDistance = 0;//�ŏI�X�R�A

/////////////////�J����//////////////////////.

float GameManager::m_cameraposx = 480.0f;
const float GameManager::m_cameraspdx = GameManager::PlayerSpd.x;


//�������֐�
void GameManager::Initialize()
{
	WorldPosX = 0.0f;
	GameOverFlag = false;//�Q�[���I�[�o�[�t���O
	InvincibleFlag = false;//���G��Ԃ��ǂ���

	JumpCnt = 0;//�W�����v�����
	JumpFlag = false;//�W�����v�ł��邩
	map.clear();//�}�b�v
	AllFloorPos.clear();//�����W
	//AllLeftPos.clear();
	//AllRightPos.clear();
	//AllLeftPos.clear();//�S�Ă̎Ζʍ��[�̍��W
	//AllRightPos.clear();//�S�Ă̎ΖʉE�[�̍��W
	MoldPos.clear();//���^�̍��W



	//////////////�L�����N�^�[���C���[//////
	//////////////�L�����N�^�[//////////////
	PlayerSpd = Vec2(6.0f, -4.0f);//���x
	PlayerSize = Vec2(96, 96);//�T�C�Y
	ScoreCorrection = 1.0f;//�X�R�A�␳
	PlayerPos = (Vec2(300.0f, GameManager::LAYRE_SIZE.y * 4));//���W
	


	FirstTouchFlag = false;//�ŏ��̃^�b�`���Ă΂ꂽ��
	PlayerMapPos = 0;//���Ԗڂ̍��W�ɂ��邩


	///////////////�X�e�[�W���C���[/////////

	MapLoopCnt = 0;//�X�e�[�W�����[�v��������


	
	
	///////////////��/////////////////////
	SlopePosY = 0.0f;//�Ζʍ��WY

	/////////////���^////////////////

	Mold = Normal;//���^
	ChangeMold = false;//���^�ω����邩


	AllLeftPos.crend();//�S�Ă̎Ζʍ��[�̍��W
	AllRightPos.crend();//�S�Ă̎ΖʉE�[�̍��W



	/////////////////UI���C���[/////////////////
	/////////////////�X�R�A////////////////
	Score = 0;//�X�R�A
	/////////////////�ꏊ////////////////////////
	SaveDistance = 0;//������ۑ�����


	/////////////////�J����//////////////////////.

	m_cameraposx = 480.0f;
}

/************************************************************************************
*|	�T�v�@�@�Փ˔��蔻��
*|	�����@�@�I�u�W�F�N�g���W,�I�u�W�F�N�g�T�C�Y,�v���C���[���W,�I�u�W�F�N�g�T�C�Y
*|�@�߂�l�@0:��	1:�}�b�v���C���[�̏�ɏ����	2:�}�b�v���C���[�̉E���ɓ�������
*************************************************************************************/
GameManager::Direction  GameManager::CollisionDetermination(Vec2 Apos,Vec2 Asize, Vec2 Bpos,Vec2 Bsize)
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
GameManager::Direction  GameManager::CollisionDetermination2(Vec2 Apos, Vec2 Asize, Vec2 Bpos, Vec2 Bsize)
{
	//�}�b�v���C���[�̏�ɏ������
	if (Apos.x <= Bpos.x + Bsize.x / 2)
	{
		if (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		{
			if (Apos.y >= Bpos.y)
			{
				if (Apos.y - BOX_COLLIDER2 <= Bpos.y)
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
				if (Apos.y - Asize.y + BOX_COLLIDER2 >= Bpos.y + Bsize.y)
				{
					{
						return under;
					}
				}
			}
		}
	}

	//�}�b�v���C���[�̍����ɓ���������
	if (Apos.x + BOX_COLLIDER2 >= Bpos.x + Bsize.x / 2)
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
	if (Apos.x + Asize.x - BOX_COLLIDER2 <= Bpos.x - Bsize.x / 2)
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

	//GameManager::SlopePosY = LineVec.y / LineVec.x  * (CirclePos.x - Apos.x) + Apos.y;


	//���ɂ��������Ă��Ȃ�
	return exception;
}



/************************************************************************************
*|	�T�v�@�@�Փ˔���(�Ε�)
*|	�����@�@�����[���W,���E�[���W,�~���S���W
*|�@�߂�l�@true���������@false �������ĂȂ�
*************************************************************************************/
GameManager::Direction GameManager::DiagonalCollisionDetermination(Vec2 Apos, Vec2 Bpos, Vec2 CirclePos) {

	//���̃x�N�g��
	Vec2 LineVec;
	//�~�Ɛ��̒��_A�̃x�N�g��
	Vec2 Avec;
	//�~�Ɛ��̒��_B�̃x�N�g��
	Vec2 Bvec;
	//���̒��_A��B�̋���
	float LineDistance;
	//���Ɖ~�̒��S����
	float Line2CircleDistance;
	//�~���㉺�ǂ��炩�瓖��������
	bool direction;

	//���̃x�N�g�������߂�
	LineVec = Bpos - Apos;
	//�~�Ɛ��̒��_AB�̃x�N�g�������ꂼ�ꋁ�߂�
	Avec = CirclePos - Apos;
	Bvec = CirclePos - Bpos;


	//Apos��Bpos�̋��������߂�
	LineDistance = Apos.distance(Bpos);

	//�O�ς��g�����Ɖ~�̒��S���������߂�
	Line2CircleDistance = LineVec.cross(Avec) / LineDistance;

	//���������Ƃ�����~���ォ�瓖������
	if (Line2CircleDistance < 0)
	{
		//���̐��ɕς���
		Line2CircleDistance *= -1.0f;
	
		direction = false;
	}
	//���������Ƃ�����~�������瓖������
	else
	{
		direction = true;
	}

	//	�������Ă��邩
	if (Line2CircleDistance <= PlayerSize.y)
	{
		//��������̔�������O����
		//�����_����~�ɐL�т���̊p���݊p�ł���ꍇ�͏Փ˂��Ȃ�
		if (Avec.dot(LineVec) * Bvec.dot(LineVec) <= 0)
		{
			//�v���C���[���ォ�瓖�������ꍇ
			if (direction == true)
			{

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



/************************************************************************************
*|	�T�v�@�@�����蔻��
*|	�����@�@�Ώۓ�̍��W
*|�@�߂�l�@true���������@false �������ĂȂ�
*************************************************************************************/
bool GameManager::HitJudgment2(Vec2 Apos, Vec2 Asize, Vec2 Bpos, Vec2 Bsize)
{

	if ((Apos.x <= Bpos.x + Bsize.x)
		&& (Apos.x + Asize.x >= Bpos.x - Bsize.x )
		&& (Apos.y >= Bpos.y)
		&& (Apos.y - Asize.y  <= Bpos.y + Bsize.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

