#pragma once

/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "cocos2d.h"
#include "../GameManager.h"

class ResultScene :public cocos2d::Scene
{
public:
	//�V�[�����쐬����
	//static cocos2d::Scene* createScene();

	CREATE_FUNC(ResultScene);
	//����������
	virtual bool init();

private:
	//���t���[���Ă΂��
	void update(float data)override;

};