/***************************************************************************
*|
*|	�T�v�@�@�G�N���X�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/5/17
*|___________________________________________________________________________
****************************************************************************/
#pragma once
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "cocos2d.h"
#include ".../../GameManager.h"

class Enemy :public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(Enemy);
	std::vector < cocos2d::Vec2> m_EnemyPos;//�����W
	const float ENEMY_SIZE = 4.0f;
private:
	


};


#pragma once