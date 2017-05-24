/***************************************************************************
*|
*|	概要　　リザルトレイヤーの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "ResultLayer.h"
#include "../TiTleScene/TitleScene.h"

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
	if (m_resultscore->TitleFlag == true)
	{
		if (CreateSprite == false)
		{
			//スプライトの生成
			s_touch = Sprite::create("Images/TouchImage.png");
			s_touch->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 2, 50));
			addChild(s_touch);
			CreateSprite = true;
		}
		VisibleCnt+=3;
		s_touch->setOpacity(VisibleCnt);
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
	if (m_resultscore->RankingFlag == true)
	{
		m_resultscore->ResultOutAction();
		//一度しか通らない
		m_resultscore->RankingFlag = false;

		MoveBy* ScoreAction = MoveBy::create(0.5f, Vec2(0, 700));
		nowscore_background->runAction(ScoreAction);
	}
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
	if (m_resultscore->TitleFlag == true)
	{
		

		Scene* nextScene = TitleScene::create();

		_director->replaceScene(nextScene);
	}
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