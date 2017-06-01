/* ---- 多重インクルードの防止 ---------- */
#pragma once

/* ----  インクルード ---------- */
#include "cocos2d.h"
#include "Character.h"

class Phoenix : public Character
{
public:
	bool init();
	CREATE_FUNC(Phoenix);

	void Animation();

private:
};
