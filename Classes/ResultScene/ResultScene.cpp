#include "ResultScene.h"
#include "Classes/PlayScene/PlayScene.h"
/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

bool ResultScene::init()
{
	// �e�N���X������������
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
