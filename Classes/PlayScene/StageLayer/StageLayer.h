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
#include "RabbitMold.h"
#include "CrayStage.h"
#include "Stage.h"
#include "Slope.h"

class StageLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(StageLayer);


private:

	////���t���[���Ăяo�����֐�
	void update(float delta)override;
	//�v���C���[�ƃR�C���̓����蔻���
	void CollisionResponseCoin();
	//�v���C���Ƌ��^�̂����蔻��
	void HittingMold();
	//���^�Ə��̂����蔻��
	void HittingFloorToMold();
	//�X�e�[�W����
	void MapCreate();
	//�X�e�[�W�폜
	void MapDelete();



	RabbitMold* Rmold;
<<<<<<< HEAD
	Slope* slope;
=======
	
>>>>>>> eb5b5cb02019439b4b6297fa3b3ec5d79ce0de9c
	Stage* stage;
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
};


