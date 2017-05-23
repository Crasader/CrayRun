/// <summary>
/// スライムキャラクター
/// GS2 24 山本悠雅
/// 2017/05/15
/// </summary>

#pragma once
/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "Character.h"

class Slime : public Character
{
public:
	bool init();
	CREATE_FUNC(Slime);

	void Move();
private:
};
