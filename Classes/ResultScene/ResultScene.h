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
#include "ui/CocosGUI.h"
#include "../GameManager.h"
#include "ResultLayer.h"
class ResultScene :public cocos2d::Scene, public cocos2d::ui::EditBoxDelegate
{
public:
	//�V�[�����쐬����
	static cocos2d::Scene* create(int score, int distance);
	//����������
	 bool init(int score,int distance);

private:
	//�^�b�`���ꂽ��
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent);
	////���t���[���Ă΂��
	//void update(float data)override;

	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)override;
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)override;
	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)override;
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox)override;
	//�A�b�v�f�[�g�֐�
	void update(float data)override;
	//���U���g���C���I�u�W�F�N�g
	ResultLayer* resultlayer;

	//��񂫂񂮃l�[���̔w�i
	cocos2d::Sprite* InputNameBackGround;
};