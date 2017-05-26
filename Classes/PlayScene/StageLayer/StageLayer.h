/***************************************************************************
*|
*|	�T�v�@�@�X�e�[�W���C���[�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/

#pragma once 
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "cocos2d.h"
#include "Coin.h"
#include "Mold.h"
#include "CrayStage.h"
#include "Stage.h"
#include "Slope.h"
#include "Needle.h"

//�L���ȃ^�b�`�̐�
const int EFFECTIVENESSTOUCH = 2;
class StageLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(StageLayer);


private:
	//�X���C�v���ɌĂяo�����
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//���t���[���Ăяo�����֐�
	void update(float delta)override;
	//�v���C���[�ƃR�C���̓����蔻���
	void CollisionResponseCoin();
	//�v���C���Ƌ��^�̂����蔻��
	void HittingMold();
	//�v���C���Ɛj�̓����蔻��
	void HittingNeedle();
	//�X�e�[�W����
	void MapCreate();
	//�X�e�[�W�폜
	void MapDelete();
	//�S�y���̃}���`�^�b�`����
	void  MultiTouchCrayStage();
	//�j�̃}���`�^�b�`����
	void  MultiTouchNeedle();

	cocos2d::Sprite* background;

	//�j
	std::vector<Needle*> needle;
	//���^�I�u�W�F�N�g
	std::vector<Mold*> mold;
	//��
	Stage* stage;
	//�S�y��
	std::vector<CrayStage*> craystage;
	//�R�C��
	std::vector<Coin*> coin;
	//�Ζ�
	std::vector<Slope*>slope;
	//�}�b�v�C�e���[�^�[
	cocos2d::Vector<cocos2d::TMXTiledMap*>::iterator IteratorMap;
	//�R�C���C�e���[�^
	cocos2d::Vector<Coin*>::iterator IteratorCoin;
	//�ΖʃC�e���[�^�[
	cocos2d::Vector<Slope*>::iterator IteratorSlope;
	//�S�y���C�e���[�^�[
	cocos2d::Vector<CrayStage*>::iterator ItratorCrayStage;
	//�j�C�e���[�^�[
	cocos2d::Vector<Needle*> ::iterator ItratorNeedle;
	//���^�C�e���[�^�[
	cocos2d::Vector<Mold*>::iterator ItratorMold;
	//�^�b�`�T�C�Y
	const cocos2d::Vec2 TOUCH_SIZE = cocos2d::Vec2(150, 150);
	const cocos2d::Vec2 TOUCH_SIZE2 = cocos2d::Vec2(30, 30);


	//�^�b�`���W
	cocos2d::Vec2 touchpos[EFFECTIVENESSTOUCH];
	//�폜����ꏊ
	int DeleteCnt;
	//�f�o�b�N�p
	cocos2d::Label* n;
	int a;
	int b;
	//�}�b�v�̐�
	const int MAX_MAP = 3;
	//�O��̃}�b�v
	int OldMap;
};


