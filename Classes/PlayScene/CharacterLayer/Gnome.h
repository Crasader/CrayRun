#pragma once

/* ---- ライブラリのインクルード ---------- */
#include "cocos2d.h"
#include "Character.h"

class Gnome : public Character
{
public:
	bool init();
	CREATE_FUNC(Gnome);


	void Animation();
private:
};
