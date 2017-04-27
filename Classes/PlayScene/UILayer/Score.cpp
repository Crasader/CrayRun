/***************************************************************************
*|
*|	�T�v�@�X�R�A�N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "Score.h"


USING_NS_CC;
using namespace cocos2d::experimental;



bool Score::init()
{
	if (!Node::init()) {

		return false;
	}

	//�����̃X�v���C�g���쐬����
	s_Number[GameManager::SpriteCnt] = Sprite::create("Images/Number.png");
	//���N�g��ݒ肷��
	s_Number[GameManager::SpriteCnt]->setTextureRect(Rect(0 * 64, 0, 64, 64));
	//���W
	s_Number[GameManager::SpriteCnt]->setPosition(Vec2(200 + 64 * GameManager::SpriteCnt, 580));
	this->addChild(s_Number[GameManager::SpriteCnt]);
	//�ő包�����L��
	GameManager::ScoreMaxDigit = GameManager::SpriteCnt;


	return true;
}


/***************************************************************************
*|	�T�v�@�@�X�R�A�̐ݒ�A�`��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void Score::ScoreIndicate(int Score)
{


	//����������������
	GameManager::Digit = 1;
	//�X�v���C�g�J�E���g������������
	GameManager::SpriteCnt = 0;
	//�Ώۂ̃X�R�A��ۑ�����
	GameManager::SaveScore = Score;

	//�X�R�A����������̂����߂�
	//�������Ȃ��Ȃ�܂�10�ŏ��Z����
	//�X�R�A��0����Ȃ��Ƃ�
	if ((Score - GameManager::SaveScore != Score))
	{
		while (Score - GameManager::SaveScore != Score)
		{
			GameManager::SaveScore /= 10;
			//���񃋁[�v�������J�E���g����
			GameManager::Digit *= 10;
		}
		//�����ɂȂ�܂ł��������A������m�肽���̂�10�Ŋ���
		GameManager::Digit /= 10;
	}

	//�Ώۂ̃X�R�A��ۑ�����
	GameManager::SaveScore = Score;

	//������0�łȂ���
	while (GameManager::Digit != 0)
	{
		//�c��̒l��0�ɂȂ鎞�A�uDigit���̒l�����߂�v�ŃG���[�ɂȂ�
		//�c��̒l��0�ɂȂ鎞�A��������0��\������
		if (GameManager::SaveScore <= 0)
		{
			//Digit���̒l�����߂�
			Score = 0;
		}
		else
		{
			//Digit���̒l�����߂�
			Score /= GameManager::Digit;
		}

		//�ő包�������������������オ������
		if (GameManager::ScoreMaxDigit < GameManager::SpriteCnt)
		{
			
				//�����̃X�v���C�g���쐬����
				s_Number[GameManager::SpriteCnt] = Sprite::create("Images/Number.png");
				//���W
				s_Number[GameManager::SpriteCnt]->setPosition(Vec2(200 + 64 * GameManager::SpriteCnt, 580));
				this->addChild(s_Number[GameManager::SpriteCnt]);
				//�ő包�����X�V����
				GameManager::ScoreMaxDigit++;
				s_Number[GameManager::SpriteCnt]->setTextureRect(Rect(Score * 64, 0, 64, 64));
		}
		//���N�g��ݒ肷��
		s_Number[GameManager::SpriteCnt]->setTextureRect(Rect(Score * 64, 0, 64, 64));

		//�X�R�A���狁�߂��l������
		GameManager::SaveScore -= Score * GameManager::Digit;
		//�X�R�A�𕜌�����
		Score = GameManager::SaveScore;
		//����Digit-1��������
		GameManager::Digit /= 10;
		//���ڂ̃X�v���C�g���J�E���g������C���N�������g
		GameManager::SpriteCnt++;
	}
}
