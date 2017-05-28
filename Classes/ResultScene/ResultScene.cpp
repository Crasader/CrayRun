
/***************************************************************************
*|
*|	概要　リザルトシーンの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/10
*|___________________________________________________________________________
****************************************************************************/
#pragma execution_character_set("utf-8")

/* ---- ライブラリのインクルード ---------- */
#include "ResultScene.h"
#include "ResultScore.h"
#include "EventListenerGesture.h"

#if (CC_TAGET_PLATFORM == CC_PLATFORM_ANDROID)
#define YUSUKE_FONT "meiryo.ttc"
#else
#define YUSUKE_FONT "Meiryo"
#endif 



/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;

//using namespace ui;


bool ResultScene::init(int score, int distance)
{
	// 親クラスを初期化する
	if (!Scene::init())
	{
		return false;
	}

	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ResultScene::onTouchBegan, this);
	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//今回のスコアを格納する
	ResultScore::m_Score = score;
	ResultScore::m_distance = distance;
	log("############################### ResultScene created");
	//ResultLayerを集約
	resultlayer = ResultLayer::create();
	this->addChild(resultlayer);


	//毎フレーム呼ぶ
	this->scheduleUpdate();
	

	//EditBox * editBox = EditBox::create(Size(400, 60), "Images/coin1.png");
	//editBox->setFont("arial", 24);
	//editBox->setPlaceHolder("aaa");
	//editBox->setFontColor(Color4B(0, 0, 0, 255));
	//editBox->setMaxLength(16);
	//editBox->setText("aaaa");
	//editBox->setReturnType(EditBox::KeyboardReturnType::DONE);
	//editBox->setInputMode(EditBox::InputMode::SINGLE_LINE);
	//editBox->setPosition(Vec2(480.0f, 320.0f));
	//editBox->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	//editBox->setDelegate(this);

	//this->addChild(editBox);
	return true;
}

/* ---- メンバー関数の定義 ---------------- */
/***************************************************************************
*|	概要　　シーンを作成する。
*|	引数　　無し
*|　戻り値　シーンのアドレス
****************************************************************************/
Scene* ResultScene::create(int score,int distance)
{
	//メモリ確保
	ResultScene *pRet = new(std::nothrow)ResultScene();

	if (pRet && pRet->init(score,distance))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
	
}


/***************************************************************************
*|	概要　　キーが押されたとき呼び出される関数
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
// タッチ開始時コールバック
bool ResultScene::onTouchBegan(Touch* touch, Event* pEvent)
{

	////フェードトランジション
	//nextScene = TransitionOriginal::create(1.0f, nextScene);
	//if (Score::SceneFlag == true)
	//{
	//	Score::SceneFlag = false;
	//	// 次のシーンを作成する
	//	Scene* nextScene = TitleScene::create();
	//	// 次のシーンに移行
	//	_director->replaceScene(nextScene);
	//}


	return true;

}

void ResultScene::editBoxEditingDidBegin(cocos2d::ui::EditBox * editBox)
{
}

void ResultScene::editBoxEditingDidEnd(cocos2d::ui::EditBox * editBox)
{
}

void ResultScene::editBoxTextChanged(cocos2d::ui::EditBox * editBox, const std::string & text)
{
}

void ResultScene::editBoxReturn(cocos2d::ui::EditBox * editBox)
{
	
		//今回ランキングインしたプレイヤー名を格納する
		ResultScore::Now_Player_Name = editBox->getText();

		//入力が終わった
		resultlayer->InputNameEndFlag = true;
		//
		InputNameBackGround->removeFromParent();
		//リザルトレイヤを再起動
		//resultlayer->resume();
		//キーボードをふっとばす
		editBox->setPosition(Vec2(1000,1000));

}

void ResultScene::update(float data)
{
	//入力するタイミングか
	if (resultlayer->InputNameFlag == true)
	{
		//リザルトシーンを止める
		//resultlayer->pause();
		//らんきんぐ名の画像
		InputNameBackGround = Sprite::create("Images/InputBackGround.png");
		InputNameBackGround->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 2, GameManager::SCREEN_SIZE.y / 2));
		this->addChild(InputNameBackGround);

		ui::EditBox * editBox = ui::EditBox::create(Size(400, 60), "Images/Input.png");
		editBox->setFont(YUSUKE_FONT, 24);
		//editBox->setPlaceHolder("おなまえ");
		editBox->setFontColor(Color4B(0, 0, 0, 255));
		editBox->setMaxLength(6);
		//editBox->setText("ここをタッチで名前入力");
		editBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
		editBox->setScale(1.3f, 1.2f);
		editBox->setInputMode(ui::EditBox::InputMode::ANY);
		editBox->setPosition(Vec2(200.0f, 150.0f));
		editBox->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		editBox->setDelegate(this);
	
		this->addChild(editBox);


		//一回しか通らない
		resultlayer->InputNameFlag = false;
	}
}
