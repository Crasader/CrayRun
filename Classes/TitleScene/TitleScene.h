/// <summary>
/// �^�C�g���V�[��
/// </summary>
#pragma once

#include <cocos2d.h>

class TitleScene : public cocos2d::Scene {
public:
	//�V�[�����쐬����
	static cocos2d::Scene* create();
	//����������
	bool init();

private:
	//�^�b�`���ꂽ��
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent);


};