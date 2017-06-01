/***************************************************************************
*|
*|	�T�v�@�����N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  �C���N���[�h ---------- */
#include "Distance.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@����
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool Distance::init()
{
	if (!Node::init()) {
		return false;
	}

	int Digit = 0;//����
	int SpriteCnt = 0;//���ڂ̃X�v���C�g���J�E���g����

	//�����̃X�v���C�g���쐬����
	s_Number[SpriteCnt] = Sprite::create("Images/Number.png");
	//���N�g��ݒ肷��
	s_Number[SpriteCnt]->setTextureRect(Rect(0 * 64, 0, 64, 64));
	//���W
	s_Number[SpriteCnt]->setPosition(Vec2(500 + 64 * SpriteCnt, 580));
	this->addChild(s_Number[SpriteCnt]);
	//�ő包�����L��
	DistanceMaxDigit = SpriteCnt;

	//���[�g���X�v���C�g�쐬
	M = Sprite::create("Images/M.png");
	M->setPosition(Vec2(500 + 64 * (SpriteCnt + 1),570));
	this->addChild(M);


	return true;
}


//�����̐ݒ�A�`��
void Distance::DistanceIndicate(int distance)
{
	//����������������
	Digit = 1;
	//�X�v���C�g�J�E���g������������
	SpriteCnt = 0;
	//�Ώۂ̋�����ۑ�����
	GameManager::SaveDistance = distance;

	//��������������̂����߂�
	//�������Ȃ��Ȃ�܂�10�ŏ��Z����
	//������0����Ȃ��Ƃ�
	if ((distance - GameManager::SaveDistance != distance))
	{
		while (distance - GameManager::SaveDistance != distance)
		{
			GameManager::SaveDistance /= 10;
			//���񃋁[�v�������J�E���g����
			Digit *= 10;
		}
		//�����ɂȂ�܂ł��������A������m�肽���̂�10�Ŋ���
		Digit /= 10;
	}

	//�Ώۂ̋�����ۑ�����
	GameManager::SaveDistance = distance;

	//������0�łȂ���
	while (Digit != 0)
	{
		//�c��̒l��0�ɂȂ鎞�A�uDigit���̒l�����߂�v�ŃG���[�ɂȂ�
		//�c��̒l��0�ɂȂ鎞�A��������0��\������
		if (GameManager::SaveDistance <= 0)
		{
			//Digit���̒l�����߂�
			distance = 0;
		}
		else
		{
			//Digit���̒l�����߂�
			distance /= Digit;
		}

		//�ő包�������������������オ������
		if (DistanceMaxDigit < SpriteCnt)
		{
			//�����̃X�v���C�g���쐬����
			s_Number[SpriteCnt] = Sprite::create("Images/Number.png");
			//���W
			s_Number[SpriteCnt]->setPosition(Vec2(500 + 50 * SpriteCnt, 580));
			M->setPosition(Vec2(500 + 64 * (SpriteCnt + 1), 570 ));

			this->addChild(s_Number[SpriteCnt]);
			//�ő包�����X�V����
			DistanceMaxDigit = SpriteCnt;
		}
		//���N�g��ݒ肷��
		s_Number[SpriteCnt]->setTextureRect(Rect(distance * 64, 0, 64, 64));

		//�������狁�߂��l������
		GameManager::SaveDistance -= distance * Digit;
		//�����𕜌�����
		distance = GameManager::SaveDistance;
		//����Digit-1��������
		Digit /= 10;
		//���ڂ̃X�v���C�g���J�E���g������C���N�������g
		SpriteCnt++;
	}
}
