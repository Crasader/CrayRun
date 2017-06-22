/***************************************************************************
*|
*|	�T�v�@�@���^�N���X���`����
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/6/1
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once
/* ----  �C���N���[�h ---------- */
#include "cocos2d.h"
#include "GameManager.h"

class Mold : public cocos2d::Node {

public:
	virtual bool init();

	CREATE_FUNC(Mold);
	std::vector<cocos2d::Sprite*> s_Mold;//���^
	std::vector<cocos2d::Sprite*> s_BackMold;//���̋��^
	std::vector<GameManager::CharacterKind> m_kind;//�L�����N�^�[�̎��
	const cocos2d::Vec2 SIZE = cocos2d::Vec2(64 * 1.6f, 64 * 1.4f);

private:
	const int m_while_distance = 25;
};