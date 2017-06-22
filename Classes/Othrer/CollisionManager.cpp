#include "CollisionManager.h"

USING_NS_CC;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}



/************************************************************************************
*|	�T�v�@�@�Փ˔��蔻��
*|	�����@�@�I�u�W�F�N�g���W,�I�u�W�F�N�g�T�C�Y,�v���C���[���W,�I�u�W�F�N�g�T�C�Y
*|�@�߂�l�@0:��	1:�}�b�v���C���[�̏�ɏ����	2:�}�b�v���C���[�̉E���ɓ�������
*************************************************************************************/
CollisionManager::Direction  CollisionManager::CollisionDetermination(Vec2 Apos, Vec2 Asize, Vec2 Bpos, Vec2 Bsize)
{
	//�}�b�v���C���[�̏�ɏ������
	if (Apos.x <= Bpos.x + Bsize.x / 2)
	{
		if (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		{
			if (Apos.y >= Bpos.y)
			{
				if (Apos.y - CollisionManager::BOX_COLLIDER <= Bpos.y)
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
				if (Apos.y - Asize.y + CollisionManager::BOX_COLLIDER >= Bpos.y + Bsize.y)
				{
					{
						return under;
					}
				}
			}
		}
	}

	//�}�b�v���C���[�̍����ɓ���������
	if (Apos.x + CollisionManager::BOX_COLLIDER >= Bpos.x + Bsize.x / 2)
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
	if (Apos.x + Asize.x - CollisionManager::BOX_COLLIDER <= Bpos.x - Bsize.x / 2)
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
CollisionManager::Direction  CollisionManager::CollisionDetermination2(Vec2 Apos, Vec2 Asize, Vec2 Bpos, Vec2 Bsize)
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



	//���ɂ��������Ă��Ȃ�
	return exception;
}



/************************************************************************************
*|	�T�v�@�@�Փ˔���(�Ε�)
*|	�����@�@�ΕӍ��[���W,�ΕӉE�[���W,�I�u�W�F�N�g���W
*|�@�߂�l�@true���������@false �������ĂȂ�
*************************************************************************************/
CollisionManager::Direction CollisionManager::DiagonalCollisionDetermination(Vec2 Apos, Vec2 Bpos, Vec2 Object) {

	Vec2 v;
	Vec2 A;
	Vec2 B;
	float w;
	float d;
	bool direction;

	//�L�����N�^�[�̒��S�����߂�
	Object.y += CollisionManager::PlayerSize.y;

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
				CollisionManager::SlopePosY = v.y / v.x  * (Object.x - Apos.x) + Apos.y; /*- GameManager::PlayerSize.y */

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
bool CollisionManager::HitJudgment(Vec2 Apos, Vec2 Asize, Vec2 Bpos, Vec2 Bsize)
{

	if ((Apos.x <= Bpos.x + Bsize.x / 2)
		&& (Apos.x + Asize.x >= Bpos.x - Bsize.x / 2)
		&& (Apos.y >= Bpos.y)
		&& (Apos.y - Asize.y / 2 <= Bpos.y + Bsize.y))
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
bool CollisionManager::HitJudgment2(Vec2 Apos, Vec2 Asize, Vec2 Bpos, Vec2 Bsize)
{

	if ((Apos.x <= Bpos.x + Bsize.x)
		&& (Apos.x + Asize.x >= Bpos.x - Bsize.x)
		&& (Apos.y >= Bpos.y)
		&& (Apos.y - Asize.y <= Bpos.y + Bsize.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

