/***************************************************************************
*|
*|	概要　スコアクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "ResultScore.h"

int ResultScore::m_Score = 0;
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


	m_node_cnt = 0;
	////数字のスプライトを作成する
	s_Number = Sprite::create("Images/Number.png");
	////レクトを設定する
	//s_Number->setTextureRect(Rect(0 * 64, 0, 64, 64));
	////座標
	//s_Number->setPosition(Vec2(200 + 64 * SpriteCnt, 580));
	//this->addChild(s_Number);
	//最大桁数を記憶
	ScoreMaxDigit = SpriteCnt;


	userDefault = cocos2d::UserDefault::getInstance();
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
}

/***************************************************************************
*|	概要　　スコアのランキングを調べる
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void ResultScore::RankingSort()
{
	//今回のスコアがランキングのどこに位置するか求める
	int i = Fifth;

	if (RankingScore[Fifth] < m_Score)
	{

		while ((RankingScore[i] < m_Score) && (i >= 0))
		{
			i--;
		}
		i++;

		//今回のスコアがランキングに入っているならば
		if (i != score)
		{
			//ランキングを入れ替える
			for (int j = 3; i <= j; j--)
			{
				RankingScore[j + 1] = RankingScore[j];
			}

			//今回のスコアをランキングに入れる
			RankingScore[i] = m_Score;
		}
	}


}

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
*|	概要　　スコアの設定、描画
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
//void ResultScore::ScoreIndicate(int Score)
//{
//
//
//	//桁数を初期化する
//	Digit = 1;
//	//スプライトカウントを初期化する
//	SpriteCnt = 0;
//	//対象のスコアを保存する
//	SaveScore = Score;
//
//	//スコアが何桁あるのか求める
//	//整数がなくなるまで10で除算する
//	//スコアが0じゃないとき
//	if ((Score - SaveScore != Score))
//	{
//		while (Score - SaveScore != Score)
//		{
//			SaveScore /= 10;
//			//何回ループしたかカウントする
//			Digit *= 10;
//		}
//		//小数になるまでかけたが、桁数を知りたいので10で割る
//		Digit /= 10;
//	}
//
//	//対象のスコアを保存する
//	SaveScore = Score;
//
//	//桁数が0でないか
//	while (Digit != 0)
//	{
//		//残りの値が0になる時、「Digit桁の値を求める」でエラーになる
//		//残りの値が0になる時、桁数分の0を表示して
//		if (SaveScore <= 0)
//		{
//			//Digit桁の値を求める
//			Score = 0;
//		}
//		else
//		{
//			//Digit桁の値を求める
//			Score /= Digit;
//		}
//
//		//最大桁数を上回ったか→桁が上がったか
//		if (ScoreMaxDigit < SpriteCnt)
//		{
//
//			//数字のスプライトを作成する
//			s_Number = Sprite::create("Images/Number.png");
//			//座標
//			s_Number->setPosition(Vec2(200 + 64 * SpriteCnt, 580));
//		/*	this->addChild(s_Number[SpriteCnt]);*/
//			//最大桁数を更新する
//			ScoreMaxDigit++;
//			s_Number->setTextureRect(Rect(Score * 64, 0, 64, 64));
//		}
//		//レクトを設定する
//		s_Number->setTextureRect(Rect(Score * 64, 0, 64, 64));
//		//基盤ノードにぶら下げる
//		node_number[m_node_cnt]->addChild(s_Number);
//		this->addChild(node_number[m_node_cnt]);
//		//スコアから求めた値を引く
//		SaveScore -= Score * Digit;
//		//スコアを復元する
//		Score = SaveScore;
//		//次はDigit-1桁を見る
//		Digit /= 10;
//		//何個目のスプライトかカウントするをインクリメント
//		SpriteCnt++;
//	}
//}


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
			s_Number->setPosition(Vec2(200 + 64 * j /*- 960*/, 500));
		}
		else
		{
			//座標
			s_Number->setPosition(Vec2(630 + 64 * j /*+ 960*/, 500 - (Ranking * 82)));
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
