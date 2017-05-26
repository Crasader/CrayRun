/***************************************************************************
*|
*|	概要　リザルトスコアクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include <stdlib.h>
#include "ResultScore.h"

int ResultScore::m_Score = 0;
int ResultScore::m_distance = 0;


/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;

bool ResultScore::init()
{
	if (!Node::init()) {
		return false;
	}
	//基盤ノードを作成する
	for (int i = 0; i < MAX_SCORE + 1; i++)
	{
		node_number[i] = Node::create();
	}

	//基盤ノードを作成する
	for (int i = 0; i < 10 + 1; i++)
	{
		now_node_number[i] = Node::create();
	}
	//初期化
	now_number = 0;

	////数字のスプライトを作成する
	s_now_number = Sprite::create("Images/Number.png");

	////数字のスプライトを作成する
	s_Number = Sprite::create("Images/Number.png");
	//最大桁数を記憶
	ScoreMaxDigit = SpriteCnt;


	userDefault = cocos2d::UserDefault::getInstance();

	//背景
	backcoin = Sprite::create("Images/ResultTexture.png");
	backcoin->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 2, GameManager::SCREEN_SIZE.y / 2));
	backcoin->setVisible(false);
	this->addChild(backcoin);

	//初期化
	ActionSpd = 0.7f;

	return true;
}

/***************************************************************************
*|	概要　　ランキングを取得する
*|	引数　　無し
*|　戻り値　無し
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
*|	概要　　スコアのランキングを調べる
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void ResultScore::RankingSort()
{
	////今回のスコアがランキングのどこに位置するか求める
	//int i = Fifth;
	//int TotalScore = m_Score + m_distance;
	//if (RankingScore[Fifth] < TotalScore)
	//{

	//	while ((RankingScore[i] < TotalScore) && (i >= 0))
	//	{
	//		i--;
	//	}
	//	i++;

	//	//今回のスコアがランキングに入っているならば
	//	if (i != score)
	//	{
	//		//ランキングを入れ替える
	//		for (int j = 3; i <= j; j--)
	//		{
	//			RankingScore[j + 1] = RankingScore[j];
	//		}

	//		//今回のスコアをランキングに入れる
	//		RankingScore[i] = m_Score;
	//	}
	//}


	

	
	//らんきんぐをソートする
	qsort(RankingScore, 6, sizeof(int), compare_int);

}


//
//int ResultScore::compare_int(const void *a, const void *b)
//{
//	return *(int *)a - *(int*)b;
//}

/***************************************************************************
*|	概要　　スコアを保存する
*|	引数　　無し
*|　戻り値　無し
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
*|	概要　　スコアのスプライト設定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void ResultScore::ScoreIndicate(int Ranking)
{

	int j;
	//桁数を初期化する
	Digit = 1;
	//対象のスコアを保存する
	SaveScore = RankingScore[Ranking];
	SaveScore2 = RankingScore[Ranking];

	//今回のスコアの場合
	if (Ranking == 5)
	{
		SaveScore = m_Score;
		SaveScore2 = m_Score;
	}

	//スコアが何桁あるのか求める
	//整数がなくなるまで10で除法する

	//スコアが0じゃないとき
	if ((SaveScore2 - SaveScore != SaveScore2))
	{
		while (SaveScore2 - SaveScore != SaveScore2)
		{
			SaveScore /= 10;
			//何回ループしたかカウントする
			Digit *= 10;

		}
		//小数になるまでかけたが、桁数を知りたいので10で割る
		Digit /= 10;
	}



	//対象のスコアを保存する
	SaveScore = RankingScore[Ranking];
	SaveScore2 = RankingScore[Ranking];
	//今回のスコアの場合
	if (Ranking == 5)
	{
		SaveScore = m_Score;
		SaveScore2 = m_Score;
	}
	j = 0;
	while (Digit != 0)
	{
		//残りの値が0になる時、「Digit桁の値を求める」でエラーになる
		//残りの値が0になる時、桁数分の0を表示して
		if (SaveScore2 <= 0)
		{
			//Digit桁の値を求める
			SaveScore = 0;
		}
		else
		{
			//Digit桁の値を求める
			SaveScore /= Digit;
		}

		//ランキングによって画像を変える
		switch (Ranking)
		{
		case First:
			//数字のスプライトを作成する
			s_Number = Sprite::create("Images/Number1.png");
			break;
		case Scound:
			//数字のスプライトを作成する
			s_Number = Sprite::create("Images/Number2.png");
			break;
		case Third:
			//数字のスプライトを作成する
			s_Number = Sprite::create("Images/Number3.png");
			break;
		default:
			//数字のスプライトを作成する
			s_Number = Sprite::create("Images/Number.png");
			break;
		}


		//レクトを設定する
		s_Number->setTextureRect(Rect(SaveScore * 64, 0, 64, 64));
		if (Ranking == 5)
		{
			//座標
			s_Number->setPosition(Vec2(400 * j /*- 960*/, 200));
		}
		else
		{
			//座標
			s_Number->setPosition(Vec2(500 + 64 * j /*+ 960*/, -150 - (Ranking * 82)));
		}

		//基盤ノードにぶら下げる
		node_number[Ranking]->addChild(s_Number);
		this->addChild(node_number[Ranking]);

		//スコアから求めた値を引く
		SaveScore2 -= SaveScore * Digit;
		SaveScore = SaveScore2;
		//次はDigit-1桁を見る
		Digit /= 10;
		j++;
	}
}


/***************************************************************************
*|	概要　　スコアのスプライト設定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void ResultScore::ScoreIndicate2(int Score)
{

	int j;
	//桁数を初期化する
	Digit = 1;
	//対象のスコアを保存する
	SaveScore = Score;
	SaveScore2 = Score;

	////今回のスコアの場合
	//if (Ranking == 5)
	//{
	//	SaveScore = m_Score;
	//	SaveScore2 = m_Score;
	//}

	//スコアが何桁あるのか求める
	//整数がなくなるまで10で除法する

	//スコアが0じゃないとき
	if ((SaveScore2 - SaveScore != SaveScore2))
	{
		while (SaveScore2 - SaveScore != SaveScore2)
		{
			SaveScore /= 10;
			//何回ループしたかカウントする
			Digit *= 10;

		}
		//小数になるまでかけたが、桁数を知りたいので10で割る
		Digit /= 10;
	}



	//対象のスコアを保存する
	SaveScore = Score;
	SaveScore2 = Score;
	////今回のスコアの場合
	//if (Ranking == 5)
	//{
	//	SaveScore = m_Score;
	//	SaveScore2 = m_Score;
	//}
	j = 0;
	while (Digit != 0)
	{
		//残りの値が0になる時、「Digit桁の値を求める」でエラーになる
		//残りの値が0になる時、桁数分の0を表示して
		if (SaveScore2 <= 0)
		{
			//Digit桁の値を求める
			SaveScore = 0;
		}
		else
		{
			//Digit桁の値を求める
			SaveScore /= Digit;
		}

	
			//数字のスプライトを作成する
		s_now_number = Sprite::create("Images/Number1_1.png");
		//レクトを設定する
		s_now_number->setTextureRect(Rect(SaveScore * 64, 0, 64, 64));

		//座標
		s_now_number->setPosition(Vec2(1100 + 64 * j , 450 - (now_number * 140)));


		//基盤ノードにぶら下げる
		now_node_number[now_number]->addChild(s_now_number);
		this->addChild(now_node_number[now_number]);

		
		//スコアから求めた値を引く
		SaveScore2 -= SaveScore * Digit;
		SaveScore = SaveScore2;
		//次はDigit-1桁を見る
		Digit /= 10;
		j++;
	}
}

//今回のスコアのアクション
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


//今回のスコアの消えるアクション
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
//	//ランキングのアクション
//	RankingAction(-1);
//	RankingOutoFlag == false;
//}

//ランキングのアクション
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




