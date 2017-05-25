/***************************************************************************
*|
*|	�T�v�@�X�R�A�N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "Score.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

bool Score::init()
{
	if (!Node::init()) {

		return false;
	}

	ScoreMaxDigit = 0;//�ő包��
	SaveScore = 0;//�X�R�A��ۑ�����
	SpriteCnt = 0;

	//�����̃X�v���C�g���쐬����
	s_Number[SpriteCnt] = Sprite::create("Images/Number.png");
	//���N�g��ݒ肷��
	s_Number[SpriteCnt]->setTextureRect(Rect(0 * 64, 0, 64, 64));
	//���W
	s_Number[SpriteCnt]->setPosition(Vec2(200 + 64 * SpriteCnt, 580));

	this->addChild(s_Number[SpriteCnt]);
	//�ő包�����L��
	ScoreMaxDigit = SpriteCnt;

	//�X�R�A(����)�̍쐬
	Sprite* s_score = Sprite::create("Images/Score.png");
	s_score->setPosition(Vec2(100, 575));
	this->addChild(s_score);
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
	Digit = 1;
	//�X�v���C�g�J�E���g������������
	SpriteCnt = 0;
	//�Ώۂ̃X�R�A��ۑ�����
	SaveScore = Score;

	//�X�R�A����������̂����߂�
	//�������Ȃ��Ȃ�܂�10�ŏ��Z����
	//�X�R�A��0����Ȃ��Ƃ�
	if ((Score - SaveScore != Score))
	{
		while (Score - SaveScore != Score)
		{
			SaveScore /= 10;
			//���񃋁[�v�������J�E���g����
			Digit *= 10;
		}
		//�����ɂȂ�܂ł��������A������m�肽���̂�10�Ŋ���
		Digit /= 10;
	}

	//�Ώۂ̃X�R�A��ۑ�����
	SaveScore = Score;

	//������0�łȂ���
	while (Digit != 0)
	{
		//�c��̒l��0�ɂȂ鎞�A�uDigit���̒l�����߂�v�ŃG���[�ɂȂ�
		//�c��̒l��0�ɂȂ鎞�A��������0��\������
		if (SaveScore <= 0)
		{
			//Digit���̒l�����߂�
			Score = 0;
		}
		else
		{
			//Digit���̒l�����߂�
			Score /= Digit;
		}

		//�ő包�������������������オ������
		if (ScoreMaxDigit < SpriteCnt)
		{
			
				//�����̃X�v���C�g���쐬����
				s_Number[SpriteCnt] = Sprite::create("Images/Number.png");
				//���W
				s_Number[SpriteCnt]->setPosition(Vec2(200 + 50 * SpriteCnt, 580));
				this->addChild(s_Number[SpriteCnt]);
				//�ő包�����X�V����
				ScoreMaxDigit++;
				s_Number[SpriteCnt]->setTextureRect(Rect(Score * 64, 0, 64, 64));
		}
		//���N�g��ݒ肷��
		s_Number[SpriteCnt]->setTextureRect(Rect(Score * 64, 0, 64, 64));

		//�X�R�A���狁�߂��l������
		SaveScore -= Score * Digit;
		//�X�R�A�𕜌�����
		Score = SaveScore;
		//����Digit-1��������
		Digit /= 10;
		//���ڂ̃X�v���C�g���J�E���g������C���N�������g
		SpriteCnt++;
	}
}
