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


	//�{�^�����쐬����
	button = ui::Button::create("Images/pause.png");
	button->setPosition(Vec2(900, 600));
	this->addChild(button);


	//�X�e�[�^�X
	status = Status::create();
	this->addChild(status);


	//////�f�o�b�N
	//String* b = String::createWithFormat("%i", 0);
	//n = Label::createWithSystemFont(b->getCString(), "arial", 60);
	//n->setScale(4.0f);
	//n->setPosition(300, 200);
	//this->addChild(n);

	button->addTouchEventListener(CC_CALLBACK_2(UiLayer::onButtonTouch, this));

	this->scheduleUpdate();

	return true;


}



/***************************************************************************
*|	�T�v�@�@�A�b�v�f�[�g�֐�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void UiLayer::update(float data) {


	//n->setString(StringUtils::toString(b));
	//n->setPositionX(spd);
	//spd += 1.2;

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


	if (GameManager::ChangeMold == true)
	{
		status->StatusAction();
		GameManager::ChangeMold = false;
	}



}

void UiLayer::onButtonTouch(Ref * ref, ui::Widget::TouchEventType eventType)
{
	switch (eventType)
	{
	case ui::Widget::TouchEventType::BEGAN:


	if (PauseFlag == false)
	{
		if (GameManager::CountDownFlag == true)
		{

			Scene* nextscene = PauseScene::create();
			_director->pushScene(nextscene);
			PauseFlag = true;
		}
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
