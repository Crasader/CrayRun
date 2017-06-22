/***************************************************************************
*|
*|	�T�v�@�@UI���C���[�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once 
/* ----  �C���N���[�h ---------- */
#include "cocos2d.h"
#include "Distance.h"
#include "Score.h"
#include "../../GameManager.h"
#include "ui/CocosGUI.h"
#include "Status.h"
#include  "Status.h"

class UiLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(UiLayer);

	void ChangeCountDownFlag() { m_CountDownFlag = true; }
private:

	////���t���[���Ăяo�����֐�
	void update(float delta)override;
	Score* score;//�X�R�A
	Distance * distance;//����
	float m_distanceSpd;//	�����ɑ����l
	cocos2d::ui::Button* button;//�{�^��

	void onButtonTouch(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType);

	//�f�o�b�N�p
	cocos2d::Label* n;
	//
	bool PauseFlag;


	//�X�e�[�^�X
	Status* status;

	//�J�E���g�_�E�����I�������
	bool m_CountDownFlag;
};


