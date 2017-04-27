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
#include "GameManager.h"
#include "Character.h"
#include "Rabbit.h"

class CharacterLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(CharacterLayer);



private:

	////���t���[���Ăяo�����֐�
	void update(float delta)override;
	//�^�b�`���ɌĂяo�����
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//�X���C�v���ɌĂяo�����
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//�^�b�`�������ꂽ
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);

	void onTouchesCancelled(const std::vector<cocos2d::Touch*>&touches, cocos2d::Event *unused_event);



	//�v���C���[�ƃX�e�[�W�̂����蔻��
	void AfterHittingFloor();
	//�v���C���[�ƎΖʂ̂����蔻��
	void AfterHittingSlope();
	//�v���C���[�ƃM�~�b�N�̂����蔻��
	//void AfterHittingGimmick();
	//�v���C���[�Ƌ��^�̂����蔻��
	//void AfterHittingMold();
	//�X�P�[���v�Z
	//void ScaleCalculation();
	//�W�����v���邩���ׂ�
	void JumpInvestigate();

	Character* character;

	cocos2d::Label* n;
	int a = 19;


	//�C�e���[�^
	cocos2d::Vector<cocos2d::Vec2>::iterator IteratorRight;
	cocos2d::Vector<cocos2d::Vec2>::iterator IteratorLeft;


};

