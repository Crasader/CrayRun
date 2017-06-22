/***************************************************************************
*|
*|	�T�v�@�@�X�e�[�W���C���[�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once 
/* ----  �C���N���[�h ---------- */
#include "cocos2d.h"
#include "Coin.h"
#include "Mold.h"
#include "CrayStage.h"
#include "Stage.h"
#include "Slope.h"
#include "Needle.h"
#include "Enemy.h"

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
	//�v���C���Ƌ��^�̂����蔻��
	void HittingMold();
	//�X�e�[�W����
	void MapCreate();
	//�X�e�[�W�폜
	void MapDelete();


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
	//�G
	std::vector<Enemy*> enemy;

	//�}�b�v�̐�
	const int MAX_MAP = 3;
	//�O��̃}�b�v
	int OldMap;
	//���^�p�[�e�B�N��
	void MoldParticle(cocos2d::Vec2 Position);
};


