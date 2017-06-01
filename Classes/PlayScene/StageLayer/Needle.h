/***************************************************************************
*|
*|	�T�v�@�@�j�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once
/* ----  �C���N���[�h ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"

class Needle :public cocos2d::Node
{
public:
	bool init();
	CREATE_FUNC(Needle);
	//�j�X�v���C�g
	std::vector<cocos2d::Sprite*> s_needle;
	//�j���
	std::vector<bool> m_needle_state;
	//�T�C�Y
	const cocos2d::Vec2 SIZE = cocos2d::Vec2(100,100);
private:
	//�C�e���[�^
	cocos2d::Vector<cocos2d::Sprite*>::iterator m_iterator_needle;
	//���ڂ����J�E���g����
	int m_needle_cnt;
};
