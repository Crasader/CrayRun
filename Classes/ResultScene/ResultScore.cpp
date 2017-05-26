/***************************************************************************
*|
*|	�T�v�@���U���g�X�R�A�N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include <stdlib.h>
#include "ResultScore.h"

int ResultScore::m_Score = 0;
int ResultScore::m_distance = 0;


/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;

bool ResultScore::init()
{
	if (!Node::init()) {
		return false;
	}
	//��Ճm�[�h���쐬����
	for (int i = 0; i < MAX_SCORE + 1; i++)
	{
		node_number[i] = Node::create();
	}

	//��Ճm�[�h���쐬����
	for (int i = 0; i < 10 + 1; i++)
	{
		now_node_number[i] = Node::create();
	}
	//������
	now_number = 0;

	////�����̃X�v���C�g���쐬����
	s_now_number = Sprite::create("Images/Number.png");

	////�����̃X�v���C�g���쐬����
	s_Number = Sprite::create("Images/Number.png");
	//�ő包�����L��
	ScoreMaxDigit = SpriteCnt;


	userDefault = cocos2d::UserDefault::getInstance();

	//�w�i
	backcoin = Sprite::create("Images/ResultTexture.png");
	backcoin->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 2, GameManager::SCREEN_SIZE.y / 2));
	backcoin->setVisible(false);
	this->addChild(backcoin);

	//������
	ActionSpd = 0.7f;

	return true;
}

/***************************************************************************
*|	�T�v�@�@�����L���O���擾����
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void ResultScore::ScoreAcquisition()
{
	RankingScore[First] = userDefault->getIntegerForKey("name1");
	RankingScore[Scound] = userDefault->getIntegerForKey("name2");
	RankingScore[Third] = userDefault->getIntegerForKey("name3");
	RankingScore[Fourth] = userDefault->getIntegerForKey("name4");
	RankingScore[Fifth] = userDefault->getIntegerForKey("name5");
	RankingScore[5] = m_Score + m_distance;
}

int compare_int(const void *a, const void *b)
{
	return *(int *)b - *(int*)a;
}

/***************************************************************************
*|	�T�v�@�@�X�R�A�̃����L���O�𒲂ׂ�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void ResultScore::RankingSort()
{
	////����̃X�R�A�������L���O�̂ǂ��Ɉʒu���邩���߂�
	//int i = Fifth;
	//int TotalScore = m_Score + m_distance;
	//if (RankingScore[Fifth] < TotalScore)
	//{

	//	while ((RankingScore[i] < TotalScore) && (i >= 0))
	//	{
	//		i--;
	//	}
	//	i++;

	//	//����̃X�R�A�������L���O�ɓ����Ă���Ȃ��
	//	if (i != score)
	//	{
	//		//�����L���O�����ւ���
	//		for (int j = 3; i <= j; j--)
	//		{
	//			RankingScore[j + 1] = RankingScore[j];
	//		}

	//		//����̃X�R�A�������L���O�ɓ����
	//		RankingScore[i] = m_Score;
	//	}
	//}


	

	
	//��񂫂񂮂��\�[�g����
	qsort(RankingScore, 6, sizeof(int), compare_int);

}


//
//int ResultScore::compare_int(const void *a, const void *b)
//{
//	return *(int *)a - *(int*)b;
//}

/***************************************************************************
*|	�T�v�@�@�X�R�A��ۑ�����
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void ResultScore::ScoreResister()
{
	userDefault->setIntegerForKey("name1", RankingScore[First] );
	userDefault->setIntegerForKey("name2", RankingScore[Scound] );
	userDefault->setIntegerForKey("name3", RankingScore[Third] );
	userDefault->setIntegerForKey("name4", RankingScore[Fourth]);
	userDefault->setIntegerForKey("name5", RankingScore[Fifth]);
	userDefault->flush();
}


/***************************************************************************
*|	�T�v�@�@�X�R�A�̃X�v���C�g�ݒ�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void ResultScore::ScoreIndicate(int Ranking)
{

	int j;
	//����������������
	Digit = 1;
	//�Ώۂ̃X�R�A��ۑ�����
	SaveScore = RankingScore[Ranking];
	SaveScore2 = RankingScore[Ranking];

	//����̃X�R�A�̏ꍇ
	if (Ranking == 5)
	{
		SaveScore = m_Score;
		SaveScore2 = m_Score;
	}

	//�X�R�A����������̂����߂�
	//�������Ȃ��Ȃ�܂�10�ŏ��@����

	//�X�R�A��0����Ȃ��Ƃ�
	if ((SaveScore2 - SaveScore != SaveScore2))
	{
		while (SaveScore2 - SaveScore != SaveScore2)
		{
			SaveScore /= 10;
			//���񃋁[�v�������J�E���g����
			Digit *= 10;

		}
		//�����ɂȂ�܂ł��������A������m�肽���̂�10�Ŋ���
		Digit /= 10;
	}



	//�Ώۂ̃X�R�A��ۑ�����
	SaveScore = RankingScore[Ranking];
	SaveScore2 = RankingScore[Ranking];
	//����̃X�R�A�̏ꍇ
	if (Ranking == 5)
	{
		SaveScore = m_Score;
		SaveScore2 = m_Score;
	}
	j = 0;
	while (Digit != 0)
	{
		//�c��̒l��0�ɂȂ鎞�A�uDigit���̒l�����߂�v�ŃG���[�ɂȂ�
		//�c��̒l��0�ɂȂ鎞�A��������0��\������
		if (SaveScore2 <= 0)
		{
			//Digit���̒l�����߂�
			SaveScore = 0;
		}
		else
		{
			//Digit���̒l�����߂�
			SaveScore /= Digit;
		}

		//�����L���O�ɂ���ĉ摜��ς���
		switch (Ranking)
		{
		case First:
			//�����̃X�v���C�g���쐬����
			s_Number = Sprite::create("Images/Number1.png");
			break;
		case Scound:
			//�����̃X�v���C�g���쐬����
			s_Number = Sprite::create("Images/Number2.png");
			break;
		case Third:
			//�����̃X�v���C�g���쐬����
			s_Number = Sprite::create("Images/Number3.png");
			break;
		default:
			//�����̃X�v���C�g���쐬����
			s_Number = Sprite::create("Images/Number.png");
			break;
		}


		//���N�g��ݒ肷��
		s_Number->setTextureRect(Rect(SaveScore * 64, 0, 64, 64));
		if (Ranking == 5)
		{
			//���W
			s_Number->setPosition(Vec2(400 * j /*- 960*/, 200));
		}
		else
		{
			//���W
			s_Number->setPosition(Vec2(500 + 64 * j /*+ 960*/, -150 - (Ranking * 82)));
		}

		//��Ճm�[�h�ɂԂ牺����
		node_number[Ranking]->addChild(s_Number);
		this->addChild(node_number[Ranking]);

		//�X�R�A���狁�߂��l������
		SaveScore2 -= SaveScore * Digit;
		SaveScore = SaveScore2;
		//����Digit-1��������
		Digit /= 10;
		j++;
	}
}


/***************************************************************************
*|	�T�v�@�@�X�R�A�̃X�v���C�g�ݒ�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void ResultScore::ScoreIndicate2(int Score)
{

	int j;
	//����������������
	Digit = 1;
	//�Ώۂ̃X�R�A��ۑ�����
	SaveScore = Score;
	SaveScore2 = Score;

	////����̃X�R�A�̏ꍇ
	//if (Ranking == 5)
	//{
	//	SaveScore = m_Score;
	//	SaveScore2 = m_Score;
	//}

	//�X�R�A����������̂����߂�
	//�������Ȃ��Ȃ�܂�10�ŏ��@����

	//�X�R�A��0����Ȃ��Ƃ�
	if ((SaveScore2 - SaveScore != SaveScore2))
	{
		while (SaveScore2 - SaveScore != SaveScore2)
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
	SaveScore2 = Score;
	////����̃X�R�A�̏ꍇ
	//if (Ranking == 5)
	//{
	//	SaveScore = m_Score;
	//	SaveScore2 = m_Score;
	//}
	j = 0;
	while (Digit != 0)
	{
		//�c��̒l��0�ɂȂ鎞�A�uDigit���̒l�����߂�v�ŃG���[�ɂȂ�
		//�c��̒l��0�ɂȂ鎞�A��������0��\������
		if (SaveScore2 <= 0)
		{
			//Digit���̒l�����߂�
			SaveScore = 0;
		}
		else
		{
			//Digit���̒l�����߂�
			SaveScore /= Digit;
		}

	
			//�����̃X�v���C�g���쐬����
		s_now_number = Sprite::create("Images/Number1_1.png");
		//���N�g��ݒ肷��
		s_now_number->setTextureRect(Rect(SaveScore * 64, 0, 64, 64));

		//���W
		s_now_number->setPosition(Vec2(1100 + 64 * j , 450 - (now_number * 140)));


		//��Ճm�[�h�ɂԂ牺����
		now_node_number[now_number]->addChild(s_now_number);
		this->addChild(now_node_number[now_number]);

		
		//�X�R�A���狁�߂��l������
		SaveScore2 -= SaveScore * Digit;
		SaveScore = SaveScore2;
		//����Digit-1��������
		Digit /= 10;
		j++;
	}
}

//����̃X�R�A�̃A�N�V����
void ResultScore::ScoreAction(int cnt)
{
	
	MoveBy* ScoreAction = MoveBy::create(ActionSpd,Vec2(-600, 0));
	CallFunc* ScoreAction2 = CallFunc::create(CC_CALLBACK_0(ResultScore::ScoreAction, this, ++cnt));
	Sequence* ScoreAction3 = Sequence::create(ScoreAction, ScoreAction2,nullptr);
	if (cnt < 3)
	{
		now_node_number[cnt]->runAction(ScoreAction3);
	}
	else
	{
		RankingFlag = true;
	}
	
}


//����̃X�R�A�̏�����A�N�V����
void ResultScore::ResultOutAction()
{

	for (int i = 0; i < 2; i++)
	{
		MoveBy* ResultAction = MoveBy::create(ActionSpd, Vec2(0.0f, 700.0f));

		now_node_number[i]->runAction(ResultAction);
	}

	
	MoveBy* ResultAction = MoveBy::create(ActionSpd, Vec2(0.0f, 700.0f));

	CallFunc* ResultAction2 = CallFunc::create(CC_CALLBACK_0(ResultScore::RankingAction, this, -1));
	Sequence* ResultAction3 = Sequence::create(ResultAction, ResultAction2, nullptr);

	now_node_number[2]->runAction(ResultAction3);
	
}
//
//
//void ResultScore::CallRankingActuin()
//{
//
//	//�����L���O�̃A�N�V����
//	RankingAction(-1);
//	RankingOutoFlag == false;
//}

//�����L���O�̃A�N�V����
void ResultScore::RankingAction(int cnt)
{
	backcoin->setVisible(true);
	MoveBy* ScoreAction = MoveBy::create(ActionSpd, Vec2(0, 600));
	CallFunc* ScoreAction2 = CallFunc::create(CC_CALLBACK_0(ResultScore::RankingAction, this, ++cnt));
	Sequence* ScoreAction3 = Sequence::create(ScoreAction, ScoreAction2, nullptr);
	if (cnt < 5)
	{
		node_number[cnt]->runAction(ScoreAction3);
	}
	else
	{
		TitleFlag = true;
	}

}




