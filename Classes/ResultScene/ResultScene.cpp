/***************************************************************************
*|
*|	概要　リザルトシーンの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/10
*|___________________________________________________________________________
****************************************************************************/
#pragma execution_character_set("utf-8")

/* ----  インクルード ---------- */
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

/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
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
		//背景を消す
		InputNameBackGround->removeFromParent();
		//左右のどーろくんを消す
		left_dorokun->removeFromParent();
		right_dorokun->removeFromParent();

		//リザルトレイヤを再起動
		//resultlayer->resume();
		//キーボードをふっとばす
		editBox->setPosition(Vec2(1000,1000));
		//リザルトBGMを再開
		experimental::AudioEngine::resume(resultlayer->ResoultBgm);
}

void ResultScene::update(float data)
{
	//入力するタイミングか
	if (resultlayer->InputNameFlag == true)
	{
		//リザルトBGMを止める
		experimental::AudioEngine::pause(resultlayer->ResoultBgm);
			
		//らんきんぐ名の画像
		InputNameBackGround = Sprite::create("Images/InputBackGround.png");
		InputNameBackGround->setPosition(Vec2(GameManager::SCREEN_SIZE.x / 2, GameManager::SCREEN_SIZE.y / 2));
		this->addChild(InputNameBackGround);

		//ドーロ君の画像（左右）
		left_dorokun = Sprite::create("Images/Player_w.png");
		right_dorokun = Sprite::create("Images/Player_w.png");

		//背景のドーロ君の座標に合わせる
		left_dorokun->setPosition(Vec2(119.0f, 163.0f));
		right_dorokun->setPosition(Vec2(832.0f, 176.0f));
		//右側のドーロ君を反転させる(X)
		right_dorokun->setFlipX(true);

		this->addChild(left_dorokun);
		this->addChild(right_dorokun);

		//点滅するアクション
		Hide* left_hideaction = Hide::create();
		Show* left_showaction = Show::create();
		DelayTime* left_delayaction = DelayTime::create(0.5f);
		Sequence* left_flashing_action = Sequence::create(left_hideaction, left_delayaction, left_showaction, left_delayaction, nullptr);
		RepeatForever* left_repeat_action = RepeatForever::create(left_flashing_action);
		//点滅するアクション(右用)
		Hide* right_hideaction = Hide::create();
		Show* right_showaction = Show::create();
		DelayTime* right_delayaction = DelayTime::create(0.5f);
		Sequence* right_flashing_action = Sequence::create(right_hideaction, right_delayaction, right_showaction, right_delayaction, nullptr);
		RepeatForever* right_repeat_action = RepeatForever::create(right_flashing_action);

		left_dorokun->runAction(left_repeat_action);
		right_dorokun->runAction(right_repeat_action);

		ui::EditBox * editBox = ui::EditBox::create(Size(400, 60), "Images/Input.png");
		editBox->setFont(YUSUKE_FONT, 24);
		//editBox->setPlaceHolder("おなまえ");
		editBox->setFontColor(Color4B(0, 0, 0, 255));
		editBox->setMaxLength(6);
		//editBox->setText("ここをタッチで名前入力");
		editBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
		editBox->setScale(1.3f, 1.2f);
		//editBox->setInputMode(ui::EditBox::InputMode::ANY);
		editBox->setPosition(Vec2(200.0f, 150.0f));
		editBox->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		editBox->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
		editBox->setDelegate(this);
	
		this->addChild(editBox);


		//一回しか通らない
		resultlayer->InputNameFlag = false;
	}
}
