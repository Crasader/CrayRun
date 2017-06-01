/***************************************************************************
*|
*|	�T�v�@���U���g�X�R�A�N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ----  �C���N���[�h ---------- */
//#include <stdlib.h>
#include "ResultScore.h"

int ResultScore::m_Score = 0;
int ResultScore::m_distance = 0;
//���񃉃��L���O�C�������v���C���[��
std::string  ResultScore::Now_Player_Name;


/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;


/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@����
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool ResultScore::init()
{
	if (!Node::init()) {
		return false;
	}
	////��Ճm�[�h���쐬����
	//for (int i = 0; i < MAX_SCORE + 1; i++)
	//{
	//	node_number[i] = Node::create();
	//}

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
	//s_Number = Sprite::create("Images/Number.png");
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

	//�����L���O�̖��O�f�[�^���擾����
	RankingName[First] = userDefault->getStringForKey("name1");
	RankingName[Scound] = userDefault->getStringForKey("name2");
	RankingName[Third] = userDefault->getStringForKey("name3");
	RankingName[Fourth] = userDefault->getStringForKey("name4");
	RankingName[Fifth] = userDefault->getStringForKey("name5");


	//�����L���O�̒l�f�[�^���擾����
	RankingScore[First] = userDefault->getIntegerForKey("ranking1");
	RankingScore[Scound] = userDefault->getIntegerForKey("ranking2");
	RankingScore[Third] = userDefault->getIntegerForKey("ranking3");
	RankingScore[Fourth] = userDefault->getIntegerForKey("ranking4");
	RankingScore[Fifth] = userDefault->getIntegerForKey("ranking5");
}

//int compare_int(const void *a, const void *b)
//{
//	return *(int *)b - *(int*)a;
//}

/***************************************************************************
*|	�T�v�@�@�X�R�A�̃����L���O�𒲂ׂ�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void ResultScore::RankingSort()
{
	////��񂫂񂮂��\�[�g����
	//qsort(RankingScore, 6, sizeof(int), compare_int);

	//����̃X�R�A�������L���O�̂ǂ��Ɉʒu���邩���߂�
	int NowRanking = Fifth;

	//����̃X�R�A
	int TotalScore = m_Score + m_distance;
	
	//if (RankingScore[Fifth] < TotalScore)
	//{
		//����̃X�R�A�͉��ʂ�
		while ((RankingScore[NowRanking] <= TotalScore) && (NowRanking >= 0))
		{
			NowRanking--;
		}

		//���炵�������̂Ŗ߂�
		NowRanking++;


		//�����L���O�����ւ���
		//�����L���O�̐����獡��̃X�R�A�����������ʂ������ă��[�v����񐔂����߂�
		for (int i = 0; i < 4 - NowRanking; i++)
		{
			//�����L���O���ЂƂ��×��Ƃ�
			RankingScore[Fifth - i] = RankingScore[Fifth - i - 1];
			//�����L���O�̖��O���ύX����
			RankingName[Fifth - i] = RankingName[Fifth - i - 1];
		}

		//����̃X�R�A�������
		RankingScore[NowRanking] = TotalScore;
		RankingName[NowRanking] = Now_Player_Name;

		//����̏��ʂ��ق�
	//	m_now_ranking[] = NowRanking;
//	}
}


void ResultScore::RankingNameSubstitution()
{
	//�f�o�b�N
	for (int i = 0; i < 5; i++)
	{
		String* a = String::createWithFormat("%d", i);
		L_PlayerName[i] = Label::createWithSystemFont(a->getCString(), "arial", 60);
		//L_PlayerName[i]->setScale(4.0f);
		L_PlayerName[i]->setString(StringUtils::toString(RankingName[i]));
		L_PlayerName[i]->setPosition(Vec2(730,-150 - (i * 82)));
		L_PlayerName[i]->setColor(Color3B(256, 256, 256));
		this->addChild(L_PlayerName[i]);
	}
}



/***************************************************************************
*|	�T�v�@�@�X�R�A��ۑ�����
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void ResultScore::ScoreResister()
{
	//�����L���O�̒l��ۑ�����
	userDefault->setIntegerForKey("ranking1", RankingScore[First]);
	userDefault->setIntegerForKey("ranking2", RankingScore[Scound] );
	userDefault->setIntegerForKey("ranking3", RankingScore[Third] );
	userDefault->setIntegerForKey("ranking4", RankingScore[Fourth]);
	userDefault->setIntegerForKey("ranking5", RankingScore[Fifth]);

	//�����L���O�̖��O��ۑ�����
	userDefault->setStringForKey("name1", RankingName[First]);
	userDefault->setStringForKey("name2", RankingName[Scound]);
	userDefault->setStringForKey("name3", RankingName[Third]);
	userDefault->setStringForKey("name4", RankingName[Fourth]);
	userDefault->setStringForKey("name5", RankingName[Fifth]);


	userDefault->flush();
}


/***************************************************************************
*|	�T�v�@�@�X�R�A�̃X�v���C�g�ݒ�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void ResultScore::ScoreIndicate(int Ranking)
{

	node_number[Ranking] = Node::create();


	int j;
	//����������������
	Digit = 1;
	//�Ώۂ̃X�R�A��ۑ�����
	SaveScore = RankingScore[Ranking];
	SaveScore2 = RankingScore[Ranking];

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
		//if (Ranking == 5)
		//{
		//	//���W
		//	s_Number->setPosition(Vec2(400 * j /*- 960*/, 200));
		//}
		/*else
		{*/
			//���W
		s_Number->setPosition(Vec2(300 + 64 * j /*+ 960*/, -150 - (Ranking * 82)));
		//}

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
	CallFunc* AudioRanking = CallFunc::create(CC_CALLBACK_0(ResultScore::PlayAudioRanking, this));
	Spawn* SpawnAction = Spawn::create(ScoreAction, AudioRanking,nullptr);
	CallFunc* ScoreAction2 = CallFunc::create(CC_CALLBACK_0(ResultScore::ScoreAction, this, ++cnt));
	Sequence* ScoreAction3 = Sequence::create(SpawnAction, ScoreAction2,nullptr);
	if (cnt < 3)
	{
		now_node_number[cnt]->runAction(ScoreAction3);
	}
	else
	{
		NowScoreOutFlag = true;
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
	CallFunc* AudioRanking = CallFunc::create(CC_CALLBACK_0(ResultScore::PlayAudioRanking, this));
	Spawn* action = Spawn::create(ScoreAction, AudioRanking, nullptr);
	CallFunc* ScoreAction2 = CallFunc::create(CC_CALLBACK_0(ResultScore::RankingAction, this, ++cnt));
	Sequence* ScoreAction3 = Sequence::create(action, ScoreAction2, nullptr);

	MoveBy* ScoreAction4 = MoveBy::create(ActionSpd, Vec2(0, 600));



	if (cnt < 5)
	{
		node_number[cnt]->runAction(ScoreAction3);
		//�����L���O�̖��O�̃A�N�V����
		L_PlayerName[cnt]->runAction(ScoreAction4);
	}
	else
	{
		TitleFlag = true;
	}

}

