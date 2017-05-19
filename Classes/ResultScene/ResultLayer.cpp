/***************************************************************************
*|
*|	概要　　リザルトレイヤーの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "ResultLayer.h"
#include "../PlayScene/PlayScene.h"

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

	// Register Touch Event
	EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(ResultLayer::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(ResultLayer::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(ResultLayer::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(ResultLayer::onTouchesCancelled, this);

	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();
	return true;
}

/***************************************************************************
*|	概要　　アップデート関数
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void ResultLayer::update(float data) {
		
}
/***************************************************************************
*|	概要　　タッチされた時に呼ぶ関数
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void ResultLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesBegan");
}
/***************************************************************************
*|	概要　　タッチしていて動いたときに呼ぶ関数
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void ResultLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesMoved");
}
/***************************************************************************
*|	概要　　タッチされたのを離した時に呼ぶ関数
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void ResultLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	GameManager::Initialize();

	Scene* nextScene = PlayScene::create();

	_director->replaceScene(nextScene);
}
/***************************************************************************
*|	概要　　タッチしているのをキャンセルしたときに呼ぶ関数
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void ResultLayer::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesCancelled");
}