/***************************************************************************
*|
*|	概要　リザルトスコアクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
//#include <stdlib.h>
#include "ResultScore.h"

int ResultScore::m_Score = 0;
int ResultScore::m_distance = 0;
//今回ランキングインしたプレイヤー名
std::string  ResultScore::Now_Player_Name;


/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;


/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool ResultScore::init()
{
	if (!Node::init()) {
		return false;
	}
	////基盤ノードを作成する
	//for (int i = 0; i < MAX_SCORE + 1; i++)
	//{
	//	node_number[i] = Node::create();
	//}

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
	//s_Number = Sprite::create("Images/Number.png");
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

	//ランキングの名前データを取得する
	RankingName[First] = userDefault->getStringForKey("name1");
	RankingName[Scound] = userDefault->getStringForKey("name2");
	RankingName[Third] = userDefault->getStringForKey("name3");
	RankingName[Fourth] = userDefault->getStringForKey("name4");
	RankingName[Fifth] = userDefault->getStringForKey("name5");


	//ランキングの値データを取得する
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
*|	概要　　スコアのランキングを調べる
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void ResultScore::RankingSort()
{
	////らんきんぐをソートする
	//qsort(RankingScore, 6, sizeof(int), compare_int);

	//今回のスコアがランキングのどこに位置するか求める
	int NowRanking = Fifth;

	//今回のスコア
	int TotalScore = m_Score + m_distance;
	
	//if (RankingScore[Fifth] < TotalScore)
	//{
		//今回のスコアは何位か
		while ((RankingScore[NowRanking] <= TotalScore) && (NowRanking >= 0))
		{
			NowRanking--;
		}

		//ずらしすぎたので戻す
		NowRanking++;


		//ランキングを入れ替える
		//ランキングの数から今回のスコアが入った順位を引いてループする回数を決める
		for (int i = 0; i < 4 - NowRanking; i++)
		{
			//ランキングをひとつずづ落とす
			RankingScore[Fifth - i] = RankingScore[Fifth - i - 1];
			//ランキングの名前も変更する
			RankingName[Fifth - i] = RankingName[Fifth - i - 1];
		}

		//今回のスコアをいれる
		RankingScore[NowRanking] = TotalScore;
		RankingName[NowRanking] = Now_Player_Name;

		//今回の順位をほぞ
	//	m_now_ranking[] = NowRanking;
//	}
}


void ResultScore::RankingNameSubstitution()
{
	//デバック
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
*|	概要　　スコアを保存する
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void ResultScore::ScoreResister()
{
	//ランキングの値を保存する
	userDefault->setIntegerForKey("ranking1", RankingScore[First]);
	userDefault->setIntegerForKey("ranking2", RankingScore[Scound] );
	userDefault->setIntegerForKey("ranking3", RankingScore[Third] );
	userDefault->setIntegerForKey("ranking4", RankingScore[Fourth]);
	userDefault->setIntegerForKey("ranking5", RankingScore[Fifth]);

	//ランキングの名前を保存する
	userDefault->setStringForKey("name1", RankingName[First]);
	userDefault->setStringForKey("name2", RankingName[Scound]);
	userDefault->setStringForKey("name3", RankingName[Third]);
	userDefault->setStringForKey("name4", RankingName[Fourth]);
	userDefault->setStringForKey("name5", RankingName[Fifth]);


	userDefault->flush();
}


/***************************************************************************
*|	概要　　スコアのスプライト設定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void ResultScore::ScoreIndicate(int Ranking)
{

	node_number[Ranking] = Node::create();


	int j;
	//桁数を初期化する
	Digit = 1;
	//対象のスコアを保存する
	SaveScore = RankingScore[Ranking];
	SaveScore2 = RankingScore[Ranking];

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
		//if (Ranking == 5)
		//{
		//	//座標
		//	s_Number->setPosition(Vec2(400 * j /*- 960*/, 200));
		//}
		/*else
		{*/
			//座標
		s_Number->setPosition(Vec2(300 + 64 * j /*+ 960*/, -150 - (Ranking * 82)));
		//}

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
	CallFunc* AudioRanking = CallFunc::create(CC_CALLBACK_0(ResultScore::PlayAudioRanking, this));
	Spawn* action = Spawn::create(ScoreAction, AudioRanking, nullptr);
	CallFunc* ScoreAction2 = CallFunc::create(CC_CALLBACK_0(ResultScore::RankingAction, this, ++cnt));
	Sequence* ScoreAction3 = Sequence::create(action, ScoreAction2, nullptr);

	MoveBy* ScoreAction4 = MoveBy::create(ActionSpd, Vec2(0, 600));



	if (cnt < 5)
	{
		node_number[cnt]->runAction(ScoreAction3);
		//ランキングの名前のアクション
		L_PlayerName[cnt]->runAction(ScoreAction4);
	}
	else
	{
		TitleFlag = true;
	}

}

