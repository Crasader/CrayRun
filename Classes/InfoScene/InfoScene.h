/***************************************************************************
*|
*|	�T�v�@�@�������N���X���`����
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/6/1
*|___________________________________________________________________________
****************************************************************************/

/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once

/* ----  �C���N���[�h ---------- */
#include <cocos2d.h>
#include <ui/CocosGUI.h>

#define MAX_INFOMATION_PASE 6

class InfoScene : public cocos2d::Scene
{
public:
	//�V�[�����쐬����
	static cocos2d::Scene* create();
	//����������
	bool init();


	//���t���[���Ăяo�����֐�
	void update(float delta)override;
private:
	cocos2d::ui::Button* b_Next;//�y�[�W���P�y�[�W�i�߂�
	cocos2d::ui::Button* b_Back;//�y�[�W���P�y�[�W�߂�
	cocos2d::ui::Button* b_BackScene;//�^�C�g���ɖ߂邽�߂̃{�^��

	void OnButtonTouchNext(cocos2d::Ref* ref,cocos2d::ui::Widget::TouchEventType eventtype);
	void OnButtonTouchBack(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventtype);



	cocos2d::Sprite* Infomation[MAX_INFOMATION_PASE];//�����摜
	int page;//�y�[�W��
	int pageCnt;
};