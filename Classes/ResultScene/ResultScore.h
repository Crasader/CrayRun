/***************************************************************************
*|
*|	概要　　スコアクラスの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
#pragma once
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "ResultLayer.h"
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
	static int m_Score;
	int m_node_cnt;
private:
	cocos2d::UserDefault* userDefault;

	enum ScoreNumber
	{
		First,
		Scound,
		Third,
		Fourth,
		Fifth,
		score
	};


	//数字スプライト
	cocos2d::Sprite* s_Number;
	int ScoreMaxDigit;//最大桁数
	int SaveScore;//スコアを保存する
	int SaveScore2;
	int Digit;//桁数
	int SpriteCnt;//何個目のスプライトかカウントする


	cocos2d::Node* node_number[MAX_SCORE + 1];



};

