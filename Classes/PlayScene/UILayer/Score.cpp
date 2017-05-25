/***************************************************************************
*|
*|	概要　スコアクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "Score.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

bool Score::init()
{
	if (!Node::init()) {

		return false;
	}

	ScoreMaxDigit = 0;//最大桁数
	SaveScore = 0;//スコアを保存する
	SpriteCnt = 0;

	//数字のスプライトを作成する
	s_Number[SpriteCnt] = Sprite::create("Images/Number.png");
	//レクトを設定する
	s_Number[SpriteCnt]->setTextureRect(Rect(0 * 64, 0, 64, 64));
	//座標
	s_Number[SpriteCnt]->setPosition(Vec2(200 + 64 * SpriteCnt, 580));

	this->addChild(s_Number[SpriteCnt]);
	//最大桁数を記憶
	ScoreMaxDigit = SpriteCnt;

	//スコア(文字)の作成
	Sprite* s_score = Sprite::create("Images/Score.png");
	s_score->setPosition(Vec2(100, 575));
	this->addChild(s_score);
	return true;
}


/***************************************************************************
*|	概要　　スコアの設定、描画
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void Score::ScoreIndicate(int Score)
{


	//桁数を初期化する
	Digit = 1;
	//スプライトカウントを初期化する
	SpriteCnt = 0;
	//対象のスコアを保存する
	SaveScore = Score;

	//スコアが何桁あるのか求める
	//整数がなくなるまで10で除算する
	//スコアが0じゃないとき
	if ((Score - SaveScore != Score))
	{
		while (Score - SaveScore != Score)
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

	//桁数が0でないか
	while (Digit != 0)
	{
		//残りの値が0になる時、「Digit桁の値を求める」でエラーになる
		//残りの値が0になる時、桁数分の0を表示して
		if (SaveScore <= 0)
		{
			//Digit桁の値を求める
			Score = 0;
		}
		else
		{
			//Digit桁の値を求める
			Score /= Digit;
		}

		//最大桁数を上回ったか→桁が上がったか
		if (ScoreMaxDigit < SpriteCnt)
		{
			
				//数字のスプライトを作成する
				s_Number[SpriteCnt] = Sprite::create("Images/Number.png");
				//座標
				s_Number[SpriteCnt]->setPosition(Vec2(200 + 50 * SpriteCnt, 580));
				this->addChild(s_Number[SpriteCnt]);
				//最大桁数を更新する
				ScoreMaxDigit++;
				s_Number[SpriteCnt]->setTextureRect(Rect(Score * 64, 0, 64, 64));
		}
		//レクトを設定する
		s_Number[SpriteCnt]->setTextureRect(Rect(Score * 64, 0, 64, 64));

		//スコアから求めた値を引く
		SaveScore -= Score * Digit;
		//スコアを復元する
		Score = SaveScore;
		//次はDigit-1桁を見る
		Digit /= 10;
		//何個目のスプライトかカウントするをインクリメント
		SpriteCnt++;
	}
}
