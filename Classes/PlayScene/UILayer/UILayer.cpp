/***************************************************************************
*|
*|	�T�v�@�@UI���C���[�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "UiLayer.h"
#include "../../PauseScene/PauseScene.h"

USING_NS_CC;

bool UiLayer::init()
{
	if (!Layer::init()) {

		return false;

	}

	//������
	m_distanceSpd = 0.18f;

	//���C���[�Ƀm�[�h���W��
    distance = Distance::create();
	this->addChild(distance);

	//���C���[�Ƀm�[�h���W��
	score = Score::create();
	this->addChild(score);

	this->scheduleUpdate();

	//�{�^�����쐬����
	button = ui::Button::create("Images/pause.jpg");
	button->setPosition(Vec2(600, 500));
	this->addChild(button);

	button->addTouchEventListener(CC_CALLBACK_2(UiLayer::onButtonTouch, this));

	return true;


}



/***************************************************************************
*|	�T�v�@�@�A�b�v�f�[�g�֐�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void UiLayer::update(float data) {
	//�X�R�A��`��
	score->ScoreIndicate(GameManager::Score);

	//�v���C���[�̑��xx�����̎�
	if (GameManager::PlayerSpd.x > 0.0f)
	{
		//�����𑝂₷
		distance->m_distance += m_distanceSpd;
		//������`��
		distance->DistanceIndicate(distance->m_distance);
		GameManager::TotalDistance = distance->m_distance;
	}


	PauseFlag = false;

}

void UiLayer::onButtonTouch(Ref * ref, ui::Widget::TouchEventType eventType)
{
	switch (eventType)
	{
	case ui::Widget::TouchEventType::BEGAN:


	if (PauseFlag == false)
	{
			Scene* nextscene = PauseScene::create();
			_director->pushScene(nextscene);
			PauseFlag = true;
	}
	

		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED:
	
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
