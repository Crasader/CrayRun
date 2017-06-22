/***************************************************************************
*|
*|	概要　　針の宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- 多重インクルードの防止 ---------- */
#pragma once
/* ----  インクルード ---------- */
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
