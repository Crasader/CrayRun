/***************************************************************************
*|
*|	�T�v�@�@�w�i���C���[�N���X
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/

/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once 
/* ----  �C���N���[�h ---------- */
#include "cocos2d.h"
#include "Background.h"

class BackgroundLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(BackgroundLayer);


private:
	Background* background;
	////���t���[���Ăяo�����֐�
	void update(float delta)override;

};

