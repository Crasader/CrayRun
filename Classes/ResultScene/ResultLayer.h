/***************************************************************************
*|
*|	概要　　リザルトレイヤーの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/10*|___________________________________________________________________________
****************************************************************************/

#pragma once 
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "ResultScore.h"



class ResultLayer :public cocos2d::Layer
{

public:
	virtual bool init();
	CREATE_FUNC(ResultLayer);
private:

	////毎フレーム呼び出される関数
	void update(float delta)override;

	//タッチ時に呼び出される
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//スワイプ時に呼び出される
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//タッチが離された
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//タッチ異常終了
	void onTouchesCancelled(const std::vector<cocos2d::Touch*>&touches, cocos2d::Event *unused_event);
	//リザルトスコア
	ResultScore* m_resultscore;
	//背景画像
	cocos2d::Sprite* nowscore_background;
	//ランキングフラグ
	bool RankingFlag;
	cocos2d::Sprite* s_touch;
	//透明度のカウント
	int VisibleCnt;
	//スプライトを生成するか
	bool CreateSprite;

};


