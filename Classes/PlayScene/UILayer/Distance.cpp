/***************************************************************************
*|
*|	概要　距離クラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "Distance.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool Distance::init()
{
	if (!Node::init()) {
		return false;
	}

	int Digit = 0;//桁数
	int SpriteCnt = 0;//何個目のスプライトかカウントする

	//数字のスプライトを作成する
	s_Number[SpriteCnt] = Sprite::create("Images/Number.png");
	//レクトを設定する
	s_Number[SpriteCnt]->setTextureRect(Rect(0 * 64, 0, 64, 64));
	//座標
	s_Number[SpriteCnt]->setPosition(Vec2(500 + 64 * SpriteCnt, 580));
	this->addChild(s_Number[SpriteCnt]);
	//最大桁数を記憶
	DistanceMaxDigit = SpriteCnt;

	//メートルスプライト作成
	M = Sprite::create("Images/M.png");
	M->setPosition(Vec2(500 + 64 * (SpriteCnt + 1),570));
	this->addChild(M);


	return true;
}


//距離の設定、描画
void Distance::DistanceIndicate(int distance)
{
	//桁数を初期化する
	Digit = 1;
	//スプライトカウントを初期化する
	SpriteCnt = 0;
	//対象の距離を保存する
	GameManager::SaveDistance = distance;

	//距離が何桁あるのか求める
	//整数がなくなるまで10で除算する
	//距離が0じゃないとき
	if ((distance - GameManager::SaveDistance != distance))
	{
		while (distance - GameManager::SaveDistance != distance)
		{
			GameManager::SaveDistance /= 10;
			//何回ループしたかカウントする
			Digit *= 10;
		}
		//小数になるまでかけたが、桁数を知りたいので10で割る
		Digit /= 10;
	}

	//対象の距離を保存する
	GameManager::SaveDistance = distance;

	//桁数が0でないか
	while (Digit != 0)
	{
		//残りの値が0になる時、「Digit桁の値を求める」でエラーになる
		//残りの値が0になる時、桁数分の0を表示して
		if (GameManager::SaveDistance <= 0)
		{
			//Digit桁の値を求める
			distance = 0;
		}
		else
		{
			//Digit桁の値を求める
			distance /= Digit;
		}

		//最大桁数を上回ったか→桁が上がったか
		if (DistanceMaxDigit < SpriteCnt)
		{
			//数字のスプライトを作成する
			s_Number[SpriteCnt] = Sprite::create("Images/Number.png");
			//座標
			s_Number[SpriteCnt]->setPosition(Vec2(500 + 50 * SpriteCnt, 580));
			M->setPosition(Vec2(500 + 64 * (SpriteCnt + 1), 570 ));

			this->addChild(s_Number[SpriteCnt]);
			//最大桁数を更新する
			DistanceMaxDigit = SpriteCnt;
		}
		//レクトを設定する
		s_Number[SpriteCnt]->setTextureRect(Rect(distance * 64, 0, 64, 64));

		//距離から求めた値を引く
		GameManager::SaveDistance -= distance * Digit;
		//距離を復元する
		distance = GameManager::SaveDistance;
		//次はDigit-1桁を見る
		Digit /= 10;
		//何個目のスプライトかカウントするをインクリメント
		SpriteCnt++;
	}
}
