/// <summary>
/// �^�C�g���̃��C���[
/// </summary>
#pragma once

#include<cocos2d.h>
#include<ui/CocosGUI.h>

class TitleLayer : public cocos2d::Layer
{
public:
	bool init();
	CREATE_FUNC(TitleLayer);


private:

	//���t���[���Ăяo�����֐�
	void update(float delta)override;


	cocos2d::ui::Button* b_start;
	cocos2d::ui::Button* b_info;
	cocos2d::ui::Button* b_exit;
};