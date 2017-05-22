/***************************************************************************
*|
*|	概要　　リザルトスコアクラスの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/10
*|___________________________________________________________________________
****************************************************************************/
#pragma once
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
/* ---- 列挙型 ---------- */
enum ScoreNumber
{
	First,
	Scound,
	Third,
	Fourth,
	Fifth,
	score
};


//ランキング数
const int MAX_SCORE = 7;
class ResultScore :public cocos2d::Node
{
public:
	virtual bool init();
	CREATE_FUNC(ResultScore);

	//スコアを取得する
	void ScoreAcquisition();
	//スコアのランキングを調べる
	void RankingSort();
	//スコアの保存
	void ScoreResister();

	//ランキングスコア
	int RankingScore[MAX_SCORE];
	//スコアの設定、描画
	void ScoreIndicate(int Score);
	//今回のスコア
	static int m_Score;
	//今回の距離
	static int m_distance;
	//今回の描画
	void ScoreIndicate2(int Score);
	//何個目の今回の数か
	int now_number;
	int ScoreMaxDigit;//最大桁数
	//今回のスコアのアクション
	void ScoreAction(int cnt);

	//ランキングフラグ
	bool RankingFlag;

	//今回の数字スプライと
	cocos2d::Sprite* s_now_number;
	//数字スプライトをぶら下げるノード
	cocos2d::Node* now_node_number[3];

private:

	cocos2d::UserDefault* userDefault;



	//数字スプライト
	cocos2d::Sprite* s_Number;

	int SaveScore;//スコアを保存する
	int SaveScore2;
	int Digit;//桁数
	int SpriteCnt;//何個目のスプライトかカウントする

	//数字スプライトをぶら下げるノード
	cocos2d::Node* node_number[MAX_SCORE + 1];

};

