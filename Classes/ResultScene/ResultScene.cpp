
/***************************************************************************
*|
*|	概要　リザルトシーンの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "ResultScene.h"
#include "ResultScore.h"
#include "ResultLayer.h"
#include "EventListenerGesture.h"




/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;




bool ResultScene::init(int score, int distance)
{
	// 親クラスを初期化する
	if (!Scene::init())
	{
		return false;
	}

	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ResultScene::onTouchBegan, this);
	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//今回のスコアを格納する
	ResultScore::m_Score = score;
	ResultScore::m_distance = distance;
	log("############################### ResultScene created");
	//ResultLayerを集約
	ResultLayer* resultlayer = ResultLayer::create();
	this->addChild(resultlayer);
	return true;
}

/* ---- メンバー関数の定義 ---------------- */
/***************************************************************************
*|	概要　　シーンを作成する。
*|	引数　　無し
*|　戻り値　シーンのアドレス
****************************************************************************/
Scene* ResultScene::create(int score,int distance)
{
	//メモリ確保
	ResultScene *pRet = new(std::nothrow)ResultScene();

	if (pRet && pRet->init(score,distance))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}

}


/***************************************************************************
*|	概要　　キーが押されたとき呼び出される関数
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
// タッチ開始時コールバック
bool ResultScene::onTouchBegan(Touch* touch, Event* pEvent)
{

	////フェードトランジション
	//nextScene = TransitionOriginal::create(1.0f, nextScene);
	//if (Score::SceneFlag == true)
	//{
	//	Score::SceneFlag = false;
	//	// 次のシーンを作成する
	//	Scene* nextScene = TitleScene::create();
	//	// 次のシーンに移行
	//	_director->replaceScene(nextScene);
	//}


	return true;

}
