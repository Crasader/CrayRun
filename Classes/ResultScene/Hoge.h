#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
//#include "SimpleAudioEngine.h"


class HogeClass : public cocos2d::Layer, public cocos2d::ui::EditBoxDelegate
{
public:
	
private:
	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox *editBox);
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox *editBox);
	virtual void editBoxTextChanged(cocos2d::ui::EditBox *editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::ui::EditBox *editBox);
};