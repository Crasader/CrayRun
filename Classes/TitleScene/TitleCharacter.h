/***************************************************************************
*|
*|	概要　　ステージクラスの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- 多重インクルードの防止 ---------- */
#pragma once
/* ----  インクルード ---------- */
#include "cocos2d.h"
#include ".../../GameManager.h"
#include "audio/include/AudioEngine.h"

class TitleChracter:public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(TitleChracter);

private:
	//ジャンプ音再生
	void PlayJumpAudio() {	//ジャンプ音再生
		cocos2d::experimental::AudioEngine::play2d("Sounds/jump04.mp3");
	}
	cocos2d::Sprite* title_character;//キャラクタ
	void update(float data)override;
	int walkCnt;
	void Animation();
	int JumpCnt;
};


