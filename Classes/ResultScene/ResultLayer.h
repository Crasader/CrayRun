/***************************************************************************
*|
*|	�T�v�@�@���U���g���C���[�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/5/10*|___________________________________________________________________________
****************************************************************************/

#pragma once 
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "cocos2d.h"
#include "ResultScore.h"



class ResultLayer :public cocos2d::Layer
{

public:
	virtual bool init();
	CREATE_FUNC(ResultLayer);
private:

	////���t���[���Ăяo�����֐�
	void update(float delta)override;

	//�^�b�`���ɌĂяo�����
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//�X���C�v���ɌĂяo�����
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//�^�b�`�������ꂽ
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//�^�b�`�ُ�I��
	void onTouchesCancelled(const std::vector<cocos2d::Touch*>&touches, cocos2d::Event *unused_event);
	//���U���g�X�R�A
	ResultScore* m_resultscore;
	//�w�i�摜
	cocos2d::Sprite* nowscore_background;
	//�����L���O�t���O
	bool RankingFlag;
	cocos2d::Sprite* s_touch;
	//�����x�̃J�E���g
	int VisibleCnt;
	//�X�v���C�g�𐶐����邩
	bool CreateSprite;

};


