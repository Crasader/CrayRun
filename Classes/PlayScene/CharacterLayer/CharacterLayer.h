/***************************************************************************
*|
*|	�T�v�@�@ResultLayer
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/

#pragma once 
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "cocos2d.h"
#include "Character.h"
#include "Rabbit.h"

class CharacterLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(CharacterLayer);


private:
	//�^�b�`���ꂽ��
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent);


	////���t���[���Ăяo�����֐�
	void update(float delta)override;

};

