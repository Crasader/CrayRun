/// <summary>
/// �X���C���L�����N�^�[
/// GS2 24 �R�{�I��
/// 2017/05/15
/// </summary>

#pragma once
/* ---- ���C�u�����̃C���N���[�h ---------- */
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
