/***************************************************************************
*|
*|	概要　　リザルトレイヤーの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ---- 多重インクルードの防止 ---------- */
#pragma once 
/* ----  インクルード ---------- */
#include "cocos2d.h"
#include "ResultScore.h"
#include "ui/CocosGUI.h"

class ResultLayer :public cocos2d::Layer
{

public:
	bool init();
	CREATE_FUNC(ResultLayer);
	//名前を入力するか
	bool InputNameFlag;
	//入力が終わったか
	bool InputNameEndFlag;
	//BGM
	int ResoultBgm;

private:

	//毎フレーム呼び出される関数
	void update(float delta)override;

	//タッチ時に呼び出される
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//スワイプ時に呼び出される
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//離したときに呼び出される
	void onTouchEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//リザルトスコア
	ResultScore* m_resultscore;
	//リザルト表示画像
	cocos2d::Sprite* nowscore_background;
	cocos2d::Sprite* backcoin;
	//ランキングフラグ
	bool RankingFlag;
	cocos2d::Sprite* s_touch;
	//透明度のカウント
	int VisibleCnt;
	//スプライトを生成するか
	bool CreateSprite;
	//画面をタッチしているか
	bool TouchFlag;
	//デバック用
	cocos2d::Label* PlayerName[5];
	bool RankingSortFlag;
};
