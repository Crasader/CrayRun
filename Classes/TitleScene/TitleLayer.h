/// <summary>
/// �^�C�g���̃��C���[
/// </summary>
#pragma once

#include<cocos2d.h>

class TitleLayer : public cocos2d::Layer
{
public:
	bool init();
	CREATE_FUNC(TitleLayer);


private:

	//���t���[���Ăяo�����֐�
	void update(float delta)override;

	//�^�b�`���ɌĂяo�����
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//�X���C�v���ɌĂяo�����
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//�^�b�`�������ꂽ
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//�^�b�`�ُ�I��
	void onTouchesCancelled(const std::vector<cocos2d::Touch*>&touches, cocos2d::Event *unused_event);

	
};