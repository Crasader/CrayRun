/***************************************************************************
*|
*|	概要　　説明書クラスを定義する
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/6/1
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "InfoScene.h"
#include "../TitleScene/TitleScene.h"
#include "../GameManager.h"
#include "audio/include/AudioEngine.h"
/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
//using namespace experimental;
using namespace std;

/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool InfoScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	
	for (int i = 0; i < MAX_INFOMATION_PASE; i++)
	{
		//説明書のスプライト生成、設定
		ostringstream ImageName;
		ImageName << "Images/Infomation/Info" << i + 1 << ".png";
		Infomation[i] = Sprite::create(ImageName.str());
		Infomation[i]->setAnchorPoint(Vec2(0, 0));
		Infomation[i]->setPosition(Vec2(i * GameManager::SCREEN_SIZE.x, 0));
		this->addChild(Infomation[i]);
	}
	

	//次へ進むボタン作成
	b_Next = ui::Button::create("Images/InfoNext.png");
	b_Next->setPosition(NEXT_POS);
	this->addChild(b_Next);

	//前に戻るボタン作成
	b_Back = ui::Button::create("Images/InfoBack.png");
	b_Back->setPosition(BACK_POS);
	this->addChild(b_Back);

	//タイトルシーンに戻るボタン作成
	b_BackScene = ui::Button::create("Images/InfoBackScene.png");
	b_BackScene->setPosition(BACK_SCENE_POS);
	this->addChild(b_BackScene);

	//ボタンから呼び出される関数を登録する
	b_Next->addTouchEventListener(CC_CALLBACK_2(InfoScene::OnButtonTouchNext, this));
	b_Back->addTouchEventListener(CC_CALLBACK_2(InfoScene::OnButtonTouchBack, this));

	//初期化処理
	page = 0;
	AnimationCnt = 0;

	//毎フレーム呼ぶ
	this->scheduleUpdate();

	return true;
}





/***************************************************************************
*|	概要　　毎フレーム呼ばれる
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void InfoScene::update(float delta)
{
	//戻るボタンが押されたとき
	if (b_BackScene->isHighlighted())
	{
		//効果音再生
		experimental::AudioEngine::play2d("Sounds/touch.mp3");
		//タイトルシーンへ
		Scene* nextscene = TitleScene::create();
		_director->pushScene(nextscene);
	}


	//アニメーションのが必要なページか
	if (page >= 1 && page <= 3)
	{
		//アニメーション用カウントをインクリメント
		AnimationCnt++;
		//10Fに一度通る
		if (AnimationCnt % ANIMATION_FLAME)
		{
			Texture2D* texture;
			ostringstream ImageName;
			if (AnimationCnt / ANIMATION_FLAME % 2)
			{
				//画像設定
				ImageName << "Images/Infomation/Info" << page+1 << ".png";
				texture = TextureCache::sharedTextureCache()->addImage(ImageName.str());
			}
			else
			{
				//画像設定
				ImageName << "Images/Infomation/Info" << page+1 << "_1" <<".png";
				texture = TextureCache::sharedTextureCache()->addImage(ImageName.str());
			}
			//画像適用
			Infomation[page]->setTexture(texture);
		}
		
	}
}



/***************************************************************************
*|	概要　　ボタンが押されたとき
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void InfoScene::OnButtonTouchNext(Ref * ref, ui::Widget::TouchEventType eventtype)
{
	switch (eventtype)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED:
		//ページが最後のページになっていない場合
		if (page < MAX_INFOMATION_PASE - 1)
		{
			//アクション実行中でないとき
			if (Infomation[0]->numberOfRunningActions() == 0)
			{
				//ページをインクリメント
				page++;
				//アニメーション用カウントを初期化する
				AnimationCnt = 0;
				//全てのページに対して横に移動するアクションを行う
				for (int i = 0; i < MAX_INFOMATION_PASE; i++)
				{

					MoveBy* ActionMove = MoveBy::create(1.0f, Vec2(-GameManager::SCREEN_SIZE.x, 0));
					Infomation[i]->runAction(ActionMove);
				}
				//スライド音再生
				experimental::AudioEngine::play2d("Sounds/SlideSE.ogg");
			}
		}
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}



/***************************************************************************
*|	概要　　ボタンが押されたとき
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void InfoScene::OnButtonTouchBack(Ref * ref, ui::Widget::TouchEventType eventtype)
{
	switch (eventtype)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED:
			//ページが最初のページになっていない場合
			if (page != 0)
			{
				//アクション実行中でないとき
				if (Infomation[0]->numberOfRunningActions() == 0)
				{
					//ページをデクリメント
					page--;
					//アニメーション用カウントを初期化する
					AnimationCnt = 0;
					//全てのページに対して横に移動するアクションを行う
					for (int i = 0; i < MAX_INFOMATION_PASE; i++)
					{
						MoveBy* ActionMove = MoveBy::create(1.0f, Vec2(GameManager::SCREEN_SIZE.x, 0));
						Infomation[i]->runAction(ActionMove);
					}
					//スライド音再生
					experimental::AudioEngine::play2d("Sounds/SlideSE.ogg");

				}
			}
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
