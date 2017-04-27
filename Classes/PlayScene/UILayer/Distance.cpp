/***************************************************************************
*|
*|	�T�v�@�����N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "Distance.h"


USING_NS_CC;
using namespace cocos2d::experimental;


bool Distance::init()
{
	if (!Node::init()) {

		return false;
	}

	//�����̃X�v���C�g���쐬����
	s_Number[GameManager::SpriteCnt] = Sprite::create("Images/Number.png");
	//���N�g��ݒ肷��
	s_Number[GameManager::SpriteCnt]->setTextureRect(Rect(0 * 64, 0, 64, 64));
	//���W
	s_Number[GameManager::SpriteCnt]->setPosition(Vec2(600 + 64 * GameManager::SpriteCnt, 580));
	this->addChild(s_Number[GameManager::SpriteCnt]);
	//�ő包�����L��
	GameManager::DistanceMaxDigit = GameManager::SpriteCnt;

	return true;
}


//�����̐ݒ�A�`��
void Distance::DistanceIndicate(int distance)
{
	//����������������
	GameManager::Digit = 1;
	//�X�v���C�g�J�E���g������������
	GameManager::SpriteCnt = 0;
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
			GameManager::Digit *= 10;
		}
		//�����ɂȂ�܂ł��������A������m�肽���̂�10�Ŋ���
		GameManager::Digit /= 10;
	}

	//�Ώۂ̋�����ۑ�����
	GameManager::SaveDistance = distance;

	//������0�łȂ���
	while (GameManager::Digit != 0)
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
			distance /= GameManager::Digit;
		}

		//�ő包�������������������オ������
		if (GameManager::DistanceMaxDigit < GameManager::SpriteCnt)
		{
			//�����̃X�v���C�g���쐬����
			s_Number[GameManager::SpriteCnt] = Sprite::create("Images/Number.png");
			//���W
			s_Number[GameManager::SpriteCnt]->setPosition(Vec2(600 + 64 * GameManager::SpriteCnt, 580));
			this->addChild(s_Number[GameManager::SpriteCnt]);
			//�ő包�����X�V����
			GameManager::DistanceMaxDigit = GameManager::SpriteCnt;
		}
		//���N�g��ݒ肷��
		s_Number[GameManager::SpriteCnt]->setTextureRect(Rect(distance * 64, 0, 64, 64));

		//�������狁�߂��l������
		GameManager::SaveDistance -= distance * GameManager::Digit;
		//�����𕜌�����
		distance = GameManager::SaveDistance;
		//����Digit-1��������
		GameManager::Digit /= 10;
		//���ڂ̃X�v���C�g���J�E���g������C���N�������g
		GameManager::SpriteCnt++;
	}
}
