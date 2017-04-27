/***************************************************************************
*|
*|	概要　距離クラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "Distance.h"


USING_NS_CC;
using namespace cocos2d::experimental;


bool Distance::init()
{
	if (!Node::init()) {

		return false;
	}

	//数字のスプライトを作成する
	s_Number[GameManager::SpriteCnt] = Sprite::create("Images/Number.png");
	//レクトを設定する
	s_Number[GameManager::SpriteCnt]->setTextureRect(Rect(0 * 64, 0, 64, 64));
	//座標
	s_Number[GameManager::SpriteCnt]->setPosition(Vec2(600 + 64 * GameManager::SpriteCnt, 580));
	this->addChild(s_Number[GameManager::SpriteCnt]);
	//最大桁数を記憶
	GameManager::DistanceMaxDigit = GameManager::SpriteCnt;

	return true;
}


//距離の設定、描画
void Distance::DistanceIndicate(int distance)
{
	//桁数を初期化する
	GameManager::Digit = 1;
	//スプライトカウントを初期化する
	GameManager::SpriteCnt = 0;
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
			GameManager::Digit *= 10;
		}
		//小数になるまでかけたが、桁数を知りたいので10で割る
		GameManager::Digit /= 10;
	}

	//対象の距離を保存する
	GameManager::SaveDistance = distance;

	//桁数が0でないか
	while (GameManager::Digit != 0)
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
			distance /= GameManager::Digit;
		}

		//最大桁数を上回ったか→桁が上がったか
		if (GameManager::DistanceMaxDigit < GameManager::SpriteCnt)
		{
			//数字のスプライトを作成する
			s_Number[GameManager::SpriteCnt] = Sprite::create("Images/Number.png");
			//座標
			s_Number[GameManager::SpriteCnt]->setPosition(Vec2(600 + 64 * GameManager::SpriteCnt, 580));
			this->addChild(s_Number[GameManager::SpriteCnt]);
			//最大桁数を更新する
			GameManager::DistanceMaxDigit = GameManager::SpriteCnt;
		}
		//レクトを設定する
		s_Number[GameManager::SpriteCnt]->setTextureRect(Rect(distance * 64, 0, 64, 64));

		//距離から求めた値を引く
		GameManager::SaveDistance -= distance * GameManager::Digit;
		//距離を復元する
		distance = GameManager::SaveDistance;
		//次はDigit-1桁を見る
		GameManager::Digit /= 10;
		//何個目のスプライトかカウントするをインクリメント
		GameManager::SpriteCnt++;
	}
}
