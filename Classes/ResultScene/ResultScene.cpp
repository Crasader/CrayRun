#include "ResultScene.h"
#include "ResultScore.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;


bool ResultScene::init(int score)
{
	// 親クラスを初期化する
	if (!Scene::init())
	{
		return false;
	}


	ResultScore::m_Score = score;
	log("############################### ResultScene created");
	//ResultLayerを集約
	ResultLayer* resultlayer = ResultLayer::create();
	this->addChild(resultlayer);
	return true;
}

//void ResultScene::update(float data)
//{
//}
/* ---- メンバー関数の定義 ---------------- */
/***************************************************************************
*|	概要　　シーンを作成する。
*|	引数　　無し
*|　戻り値　シーンのアドレス
****************************************************************************/
Scene* ResultScene::create(int score)
{
	//メモリ確保
	ResultScene *pRet = new(std::nothrow)ResultScene();

	if (pRet && pRet->init(score))
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