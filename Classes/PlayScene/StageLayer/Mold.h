//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//
//�@�t�@�C�����FMold.h
//
//	�T�@�@�@�v�F���^
//
//�@��@���@�ҁFGS2 24 �R�{�I��
//
//�@��@���@���F2017/05/02
//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
//���C�u�����̃C���N���[�h/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "cocos2d.h"
#include "GameManager.h"

class Mold : public cocos2d::Node {

public:
	virtual bool init();

	CREATE_FUNC(Mold);
	std::vector<cocos2d::Sprite*> s_Mold;//���^
	std::vector<cocos2d::Sprite*> s_BackMold;//���̋��^
	std::vector<CharacterKind> m_kind;//�L�����N�^�[�̎��
	const cocos2d::Vec2 SIZE = cocos2d::Vec2(64 * 2.0f, 64 * 1.8f);

private:
	const int m_while_distance = 25;
};