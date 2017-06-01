/***************************************************************************
*|
*|	�T�v�@�@���U���g���C���[�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/5/10
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once 
/* ----  �C���N���[�h ---------- */
#include "cocos2d.h"
#include "ResultScore.h"
#include "ui/CocosGUI.h"

class ResultLayer :public cocos2d::Layer
{

public:
	bool init();
	CREATE_FUNC(ResultLayer);
	//���O����͂��邩
	bool InputNameFlag;
	//���͂��I�������
	bool InputNameEndFlag;
	//BGM
	int ResoultBgm;

private:

	//���t���[���Ăяo�����֐�
	void update(float delta)override;

	//�^�b�`���ɌĂяo�����
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//�X���C�v���ɌĂяo�����
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//�������Ƃ��ɌĂяo�����
	void onTouchEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//���U���g�X�R�A
	ResultScore* m_resultscore;
	//���U���g�\���摜
	cocos2d::Sprite* nowscore_background;
	cocos2d::Sprite* backcoin;
	//�����L���O�t���O
	bool RankingFlag;
	cocos2d::Sprite* s_touch;
	//�����x�̃J�E���g
	int VisibleCnt;
	//�X�v���C�g�𐶐����邩
	bool CreateSprite;
	//��ʂ��^�b�`���Ă��邩
	bool TouchFlag;
	//�f�o�b�N�p
	cocos2d::Label* PlayerName[5];
	bool RankingSortFlag;
};
