//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//
//
//
//
//
//
//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#include "ResultScene.h"
/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

bool ResultScene::init()
{
	// 親クラスを初期化する
	if (!Scene::init())
	{
		return false;
	}

	log("############################### ResultScene created");

	return true;
}

void ResultScene::update(float data)
{
}
