#pragma once


#include "cocos2d.h"
#include "StageLayer\StageLayer.h"
#include "BackgroundLayer\BackgroundLayer.h"
#include "CharacterLayer\CharacterLayer.h"
#include "UILayer\UILayer.h"


class PlayScene :public cocos2d::Scene
{
public:
	//ƒV[ƒ“‚ğì¬‚·‚é
	static cocos2d::Scene* createScene();
	CREATE_FUNC(PlayScene);
	//‰Šú‰»‚·‚é
	virtual bool init();

private:

};