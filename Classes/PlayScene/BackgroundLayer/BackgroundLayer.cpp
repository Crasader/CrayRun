/***************************************************************************
*|
*|	概要　　背景リザルトレイヤー
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "BackgroundLayer.h"
#include "../../GameManager.h"
/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;


/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool BackgroundLayer::init()
{
	if (!Layer::init()) {

		return false;

	}

	//レイヤーにノードを集約
	background = Background::create();
	this->addChild(background);




	//毎フレーム呼び出す
	this->scheduleUpdate();
	return true;

}



void BackgroundLayer::update(float data) 
{
	if (GameManager::m_cameraposx == 480 + GameManager::m_cameraspdx)
	{

		background->scheduleUpdate();
	}
};
