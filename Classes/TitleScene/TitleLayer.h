/***************************************************************************
*|
*|	�T�v�@�@�^�C�g�����C���N���X���`����
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/6/1
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once

/* ---- �C���N���[�h ---------- */
#include<cocos2d.h>
#include<ui/CocosGUI.h>
#include "../PlayScene/PlayScene.h"

class TitleLayer : public cocos2d::Layer
{
public:
	bool init();
	CREATE_FUNC(TitleLayer)


private:

	//���t���[���Ăяo�����֐�
	void update(float delta)override;


	cocos2d::ui::Button* b_start;
	cocos2d::ui::Button* b_info;
	cocos2d::ui::Button* b_exit;
	int TitleBgm;

};