/***************************************************************************
*|
*|	�T�v�@�@�������N���X���`����
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/6/1
*|___________________________________________________________________________
****************************************************************************/

/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once

/* ----  �C���N���[�h ---------- */
#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include "../GameManager.h"

//�y�[�W��
#define MAX_INFOMATION_PASE 7

class InfoScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(InfoScene);
	//����������
	bool init();


	//���t���[���Ăяo�����֐�
	void update(float delta)override;
private:
	cocos2d::ui::Button* b_Next;//�y�[�W���P�y�[�W�i�߂�{�^��
	cocos2d::ui::Button* b_Back;//�y�[�W���P�y�[�W�߂��{�^��
	cocos2d::ui::Button* b_BackScene;//�^�C�g���ɖ߂邽�߂̃{�^��




	//�y�[�W���P�y�[�W�i�߂�{�^���̍��W
	const cocos2d::Vec2 NEXT_POS = cocos2d::Vec2(GameManager::SCREEN_SIZE.x - GameManager::SCREEN_SIZE.x / 5.0f, 100.0f);
	//�y�[�W���P�y�[�W�߂��{�^���̍��W
	const cocos2d::Vec2 BACK_POS = cocos2d::Vec2(GameManager::SCREEN_SIZE.x / 5.0f, 100.0f);
	//�^�C�g���ɖ߂邽�߂̃{�^���̍��W
	const cocos2d::Vec2 BACK_SCENE_POS = cocos2d::Vec2(GameManager::SCREEN_SIZE.x / 2.0f, 100.0f);


	//�{�^���������ꂽ�Ƃ��Ăяo�����֐�
	void OnButtonTouchNext(cocos2d::Ref* ref,cocos2d::ui::Widget::TouchEventType eventtype);
	void OnButtonTouchBack(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventtype);



	cocos2d::Sprite* Infomation[MAX_INFOMATION_PASE];//�����摜
	int page;//�y�[�W��
	int AnimationCnt;//�A�j���[�V�����p�J�E���g
	const int ANIMATION_FLAME = 10;

};