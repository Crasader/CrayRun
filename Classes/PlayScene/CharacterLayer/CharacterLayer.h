/***************************************************************************
*|
*|	�T�v�@�@�L�����N�^�[���C���[�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/

#pragma once 
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"
#include "Character.h"
#include "Rabbit.h"
#include "Slime.h"
#include "Gnome.h"
#include "Phoenix.h"

#include "Status.h"



//�L���ȃ^�b�`�̐�
static const int EFFECTIVENESS_TOUCH = 2;
class CharacterLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(CharacterLayer);



private:


	//���t���[���Ăяo�����֐�
	void update(float delta)override;
	//�^�b�`���ɌĂяo�����
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//�X���C�v���ɌĂяo�����
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//�^�b�`�������ꂽ
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//�^�b�`�ُ�I��
	void onTouchesCancelled(const std::vector<cocos2d::Touch*>&touches, cocos2d::Event *unused_event);

	//�L�����N�^�[�̃}���`�^�b�`����
	void  MultiTouchCharacter();


	//���^�̕ύX
	void ChangeMold();
	//�v���C���[�ƃX�e�[�W�̂����蔻��
	void CollisionResponseFloor();
	//�v���C���[�ƔS�y���̂����蔻��
	void CollisionResponseCrayFloor();
	//�v���C���[�ƎΖʂ̂����蔻��
	void  CollisionResponseSlope();
	//�v���C���[�ƃM�~�b�N�̂����蔻��
	//void AfterHittingGimmick();

	//�W�����v���邩���ׂ�
	void JumpInvestigate();
	//�L�����N�^�[�I�u�W�F�N�g
	Character* character;

	Status* status;

	//�f�o�b�N�p
	cocos2d::Label* n;
	int a = 19;
	int b = 0;
	

	//�^�b�`ID�i�[
	int m_touch_id;
	
	//�^�b�`���W
	cocos2d::Vec2 touchpos[EFFECTIVENESS_TOUCH];
	//�C�e���[�^
	cocos2d::Vector<cocos2d::Vec2>::iterator IteratorRight;
	cocos2d::Vector<cocos2d::Vec2>::iterator IteratorLeft;


	//�^�b�`�T�C�Y
	const cocos2d::Vec2 TOUCH_SIZE = cocos2d::Vec2(60,60);
	int FirstTouchCnt;//�ŏ��̃^�b�`����ǂꂾ���o�߂�����
	bool FirstTouchFlag = false;//�ŏ��̃^�b�`���Ă΂ꂽ��

};

