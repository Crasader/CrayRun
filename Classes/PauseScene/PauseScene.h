/***************************************************************************
*|
*|	�T�v�@���U���g�V�[���̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/5/10
*|___________________________________________________________________________
****************************************************************************/

#pragma once

/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "cocos2d.h"
#include "../GameManager.h"
#include "ui/CocosGUI.h"

class PauseScene :public cocos2d::Scene
{
public:

	//����������
	bool init();
	CREATE_FUNC(PauseScene);

private:
	//�^�b�`���ꂽ��
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent);
	////���t���[���Ă΂��
	void update(float data)override;
	cocos2d::ui::Button* CountinueButton;//�{�^��

	cocos2d::ui::Button* TitleButton;//�{�^��

};