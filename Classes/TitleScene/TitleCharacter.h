/***************************************************************************
*|
*|	�T�v�@�@�X�e�[�W�N���X�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once
/* ----  �C���N���[�h ---------- */
#include "cocos2d.h"
#include ".../../GameManager.h"
#include "audio/include/AudioEngine.h"

class TitleChracter:public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(TitleChracter);

private:
	//�W�����v���Đ�
	void PlayJumpAudio() {	//�W�����v���Đ�
		cocos2d::experimental::AudioEngine::play2d("Sounds/jump04.mp3");
	}
	cocos2d::Sprite* title_character;//�L�����N�^
	void update(float data)override;
	int walkCnt;
	void Animation();
	int JumpCnt;
};


