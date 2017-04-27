/***************************************************************************
*|
*|	概要　スコアクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "Score.h"


USING_NS_CC;
using namespace cocos2d::experimental;



bool Score::init()
{
	if (!Node::init()) {

		return false;
	}

	//数字のスプライトを作成する
	s_Number[GameManager::SpriteCnt] = Sprite::create("Images/Number.png");
	//レクトを設定する
	s_Number[GameManager::SpriteCnt]->setTextureRect(Rect(0 * 64, 0, 64, 64));
	//座標
	s_Number[GameManager::SpriteCnt]->setPosition(Vec2(200 + 64 * GameManager::SpriteCnt, 580));
	this->addChild(s_Number[GameManager::SpriteCnt]);
	//最大桁数を記憶
	GameManager::ScoreMaxDigit = GameManager::SpriteCnt;


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
	GameManager::Digit = 1;
	//スプライトカウントを初期化する
	GameManager::SpriteCnt = 0;
	//対象のスコアを保存する
	GameManager::SaveScore = Score;

	//スコアが何桁あるのか求める
	//整数がなくなるまで10で除算する
	//スコアが0じゃないとき
	if ((Score - GameManager::SaveScore != Score))
	{
		while (Score - GameManager::SaveScore != Score)
		{
			GameManager::SaveScore /= 10;
			//何回ループしたかカウントする
			GameManager::Digit *= 10;
		}
		//小数になるまでかけたが、桁数を知りたいので10で割る
		GameManager::Digit /= 10;
	}

	//対象のスコアを保存する
	GameManager::SaveScore = Score;

	//桁数が0でないか
	while (GameManager::Digit != 0)
	{
		//残りの値が0になる時、「Digit桁の値を求める」でエラーになる
		//残りの値が0になる時、桁数分の0を表示して
		if (GameManager::SaveScore <= 0)
		{
			//Digit桁の値を求める
			Score = 0;
		}
		else
		{
			//Digit桁の値を求める
			Score /= GameManager::Digit;
		}

		//最大桁数を上回ったか→桁が上がったか
		if (GameManager::ScoreMaxDigit < GameManager::SpriteCnt)
		{
			
				//数字のスプライトを作成する
				s_Number[GameManager::SpriteCnt] = Sprite::create("Images/Number.png");
				//座標
				s_Number[GameManager::SpriteCnt]->setPosition(Vec2(200 + 64 * GameManager::SpriteCnt, 580));
				this->addChild(s_Number[GameManager::SpriteCnt]);
				//最大桁数を更新する
				GameManager::ScoreMaxDigit++;
				s_Number[GameManager::SpriteCnt]->setTextureRect(Rect(Score * 64, 0, 64, 64));
		}
		//レクトを設定する
		s_Number[GameManager::SpriteCnt]->setTextureRect(Rect(Score * 64, 0, 64, 64));

		//スコアから求めた値を引く
		GameManager::SaveScore -= Score * GameManager::Digit;
		//スコアを復元する
		Score = GameManager::SaveScore;
		//次はDigit-1桁を見る
		GameManager::Digit /= 10;
		//何個目のスプライトかカウントするをインクリメント
		GameManager::SpriteCnt++;
	}
}
