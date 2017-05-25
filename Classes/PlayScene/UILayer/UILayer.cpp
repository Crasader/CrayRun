/***************************************************************************
*|
*|	概要　　UIレイヤーの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "UiLayer.h"
#include "../../PauseScene/PauseScene.h"

USING_NS_CC;

bool UiLayer::init()
{
	if (!Layer::init()) {

		return false;

	}

	//初期化
	m_distanceSpd = 0.18f;

	//レイヤーにノードを集約
    distance = Distance::create();
	this->addChild(distance);

	//レイヤーにノードを集約
	score = Score::create();
	this->addChild(score);


	//ボタンを作成する
	button = ui::Button::create("Images/pause.png");
	button->setPosition(Vec2(900, 600));
	this->addChild(button);


	//ステータス
	status = Status::create();
	this->addChild(status);


	//////デバック
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
*|	概要　　アップデート関数
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void UiLayer::update(float data) {


	//n->setString(StringUtils::toString(b));
	//n->setPositionX(spd);
	//spd += 1.2;

	//スコアを描画
	score->ScoreIndicate(GameManager::Score);

	//プレイヤーの速度xが正の時
	if (GameManager::PlayerSpd.x > 0.0f)
	{

		//距離を増やす
		distance->m_distance += m_distanceSpd;
		//距離を描画
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
