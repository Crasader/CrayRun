#pragma once

/* ---- ���C�u�����̃C���N���[�h ---------- */
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
