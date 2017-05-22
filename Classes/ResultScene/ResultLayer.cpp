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

	//背景
	Sprite* backcoin = Sprite::create("Images/Result.png");
	backcoin->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 2, GameManager::SCREEN_SIZE.y / 2));
	backcoin->setScale(1.5f, 1.4f);
	this->addChild(backcoin);

	//背景
	nowscore_background = Sprite::create("Images/NowScore.png");
	nowscore_background->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 2, GameManager::SCREEN_SIZE.y / 2));
	this->addChild(nowscore_background);






	//スコア作成
	m_resultscore = ResultScore::create();
	this->addChild(m_resultscore);
	//今回のスコアのアクション
	m_resultscore->ScoreAction(-1);

	//スコアを取得する
	m_resultscore->ScoreAcquisition();
	//スコアのランキングを調べる
	m_resultscore->RankingSort();
	//スコアの保存
	m_resultscore->ScoreResister();



	//今回のスコア、距離、合計スコアを格納する
	int nowscore[3] = { ResultScore::m_Score,ResultScore::m_distance,ResultScore::m_Score + ResultScore::m_distance };
	for (int i = 0; i < 3; i++)
	{

		m_resultscore->ScoreIndicate2(nowscore[i]);

		m_resultscore->ScoreMaxDigit = 0;
		m_resultscore->now_number++;

	}

	//スコアの設定、描画
	for (int i = 0; i < 5; i++)
	{
		m_resultscore->ScoreIndicate(i);
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
void ResultLayer::update(float data)
{
	if (m_resultscore->RankingFlag == true)
	{

		//今回の数字スプライと
		cocos2d::Sprite* s_now_number;
		for (int i = 0; i < 3; i++)
		{
			MoveBy* ResultAction = MoveBy::create(3.0f, Vec2(0.0f, 300.0f));
			m_resultscore->now_node_number[i]->runAction(ResultAction);
		}
	
	}
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