/***************************************************************************
*|
*|	�T�v�@�@�j�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once
/* ----  �C���N���[�h ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"
#include "NeedleSprite.h"
class Needle :public cocos2d::Node
{
public:
	bool init();
	CREATE_FUNC(Needle);
	std::vector<NeedleSprite*> m_needleSprite;
private:
};
