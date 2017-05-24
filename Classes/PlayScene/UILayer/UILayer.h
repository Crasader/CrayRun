/***************************************************************************
*|
*|	�T�v�@�@UI���C���[�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/

#pragma once 
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "cocos2d.h"
#include "Distance.h"
#include "Score.h"
#include "../../GameManager.h"
#include "ui/CocosGUI.h"


class UiLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(UiLayer);


private:

	////���t���[���Ăяo�����֐�
	void update(float delta)override;
	Score* score;//�X�R�A
	Distance * distance;//����
	float m_distanceSpd;//	�����ɑ����l
	cocos2d::ui::Button* button;//�{�^��

	void onButtonTouch(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType);

	bool PauseFlag;
};


