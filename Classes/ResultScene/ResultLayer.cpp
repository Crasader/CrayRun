/***************************************************************************
*|
*|	概要　　リザルトレイヤーの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "ResultLayer.h"

USING_NS_CC;

bool ResultLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	//スコア作成
	ResultScore* resultscore = ResultScore::create();
	this->addChild(resultscore);
	//スコアを取得する
	resultscore->ScoreAcquisition();
	//スコアのランキングを調べる
	resultscore->RankingSort();
	//スコアの保存
	resultscore->ScoreResister();
	//スコアの設定、描画
	for (int i = 0; i < 5; i++)
	{
		resultscore->ScoreIndicate(i);
	}
	this->scheduleUpdate();
	return true;
}



/***************************************************************************
*|	概要　　アップデート関数
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void ResultLayer::update(float data) {

};