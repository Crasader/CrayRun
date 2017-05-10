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

	RabbitMold* Rmold;
	//Slope* slope;
	Stage* stage;
	//�R�C��
	std::vector<Coin*> coin;
	//�R�C���C�e���[�^
	cocos2d::Vector<Coin*>::iterator IteratorCoin;
	
};


