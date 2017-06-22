/***************************************************************************
*|
*|	概要　　キャラクターレイヤークラス
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "CharacterLayer.h"


/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace experimental;

/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool CharacterLayer::init()
{
	if (!Layer::init()) {

		return false;

	}

	//レイヤーにノードを集約
	character = Character::create();
	this->addChild(character);
	
	//毎フレーム呼び出す
	this->scheduleUpdate();


	// Register Touch Event
	EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(CharacterLayer::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(CharacterLayer::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(CharacterLayer::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(CharacterLayer::onTouchesCancelled, this);

	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//_touchListener = listener;
	int FirstTouchCnt = 0;//最初のタッチからどれだけ経過したか


	return true;
}

/***************************************************************************
*|	概要　	毎フレーム呼び出す
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::update(float date)
{
	//金型が変更されている場合
	if (GameManager::ChangeMold == true) {
		//型を変更する
		ChangeMold();
	}

	//移動する
	character->Move();
	//重力
	character->Gravity();
	//何番目のマップにいるか求める
	character->GetLoopPos();


	//プレイヤーと床の衝突判定
	CollisionResponseFloor();
	//ジャンプするか調べる
	JumpInvestigate();
	//サイズ変更
	character->setScale();
	//キャラクタ上方向上限
	character->JumpBan();





	//ジャンプの命令が終わったことにする
	if (GameManager::PlayerSpd.y < 4)
	{
		GameManager::JumpState = false;
	}




}


/***************************************************************************
*|	概要　	タッチ時に呼び出される
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{	


	for (auto &item : touches)
	{
		//タッチのアドレスを格納する
		auto touch = item;
	
		if (FirstTouchFlag == false)
		{
			
			//最初のタッチが呼ばれたら真
			//次のタッチまでのカウントを始める
			FirstTouchFlag = true;
			
		}
		else
		{
			//最初のタッチフラグを偽にする
			FirstTouchFlag = false;
			//最初のタッチカウントを初期化する
			FirstTouchCnt = 0;
		}
	}
	log("onTouchesBegan");
	
}

/***************************************************************************
*|	概要　	スワイプ時に呼び出される
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesMoved");
	//タッチの数だけループ
	for (auto &item : touches)
	{
		//タッチのIDを取得する
		auto touch = item;
		m_touch_id = touch->getID();
	
		//3つ目以上のタッチは受け付けない
		if (m_touch_id < 2)
		{
			//座標を取得する
			touchpos[m_touch_id] = touch->getLocation();
			touchpos[m_touch_id].x += GameManager::m_cameraposx - 480;
		}
	}




	////二回以上タッチされたら
	if (m_touch_id >= 1)
	{

	//	if (FirstMultiTouchFlag == false)
	//	{
	//		for (int i = 0; i < EFFECTIVENESS_TOUCH; i++)
	//		{
	//			FirstPos[i] = touchpos[i];
	//			SavePlayerPosx = GameManager::PlayerPos.x;
	//		}
	//		FirstMultiTouchFlag = true;
	//キャラクターのマルチタッチ判定
		MultiTouchCharacter();
		}


		

	//	//初期化する
	//	touchpos[0] = Vec2(0.0f, 0.0f);
	//	touchpos[1] = Vec2(0.0f, 0.0f);
	//}
}

/***************************************************************************
*|	概要　	離したとき
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesEnded");

	//for (int i = 0; i < EFFECTIVENESS_TOUCH; i++)
	//{
	//	FirstPos[i] = Vec2(0.0f, 0.0f);
	//}

}

/***************************************************************************
*|	概要　	キャンセルされたとき
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesCancelled");
}


/***************************************************************************
*|	概要　	キャラクターのマルチタッチ判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::MultiTouchCharacter()
{
	////タッチが当たった方向
	//Direction m_touch_collision_direction[EFFECTIVENESS_TOUCH];
	//タッチがキャラクターに当たったか
	bool m_touch_collision[EFFECTIVENESS_TOUCH];

	//タッチがプレイヤーに当たったか
	m_touch_collision[0] = GameManager::HitJudgment2(
		touchpos[0] /*- Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2)*/, Vec2(0,0),
	Vec2(GameManager::PlayerPos.x - GameManager::PlayerSize.x/ 2 - GameManager::PlayerSize.x, 
		GameManager::PlayerPos.y), GameManager::PlayerSize);
	
	if (m_touch_collision[0] == true && character->isScale == false)
	{
		GameManager::PlayerSize.x = 16;
		character->isScale = true;
		PlaySandWicheSE();
	}


	//タッチがプレイヤーに当たったか
	m_touch_collision[0] = GameManager::HitJudgment2(
		touchpos[1]/* - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2)*/, Vec2(0, 0),
		Vec2(GameManager::PlayerPos.x - GameManager::PlayerSize.x / 2 - GameManager::PlayerSize.x,
			GameManager::PlayerPos.y), GameManager::PlayerSize);

	if (m_touch_collision[0] == true && character->isScale == false)
	{
		GameManager::PlayerSize.x = 16;
		character->isScale = true;
		PlaySandWicheSE();
	}


	//タッチがプレイヤーに当たったか
	m_touch_collision[0] = GameManager::HitJudgment2(
		touchpos[0] /*- Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2)*/, Vec2(0,0),
		Vec2(GameManager::PlayerPos.x + GameManager::PlayerSize.x / 2 ,
			GameManager::PlayerPos.y  ), GameManager::PlayerSize);
	if (m_touch_collision[0] == true && character->isScale == false)
	{
		GameManager::PlayerSize.x = 16;
		character->isScale = true;
		PlaySandWicheSE();
	}



	//タッチ2がプレイヤーに当たったか
	m_touch_collision[1] = GameManager::HitJudgment2(
		touchpos[0] /*- Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2)*/, Vec2(0, 0),
		Vec2(GameManager::PlayerPos.x - GameManager::PlayerSize.x/2,
			GameManager::PlayerPos.y + GameManager::PlayerSize.y ), GameManager::PlayerSize);

	
	if (m_touch_collision[1] == true && character->isScale == false)
	{
		GameManager::PlayerSize.y = 32;
		character->isScale = true;
		PlaySandWicheSE();
	}

	//タッチ2がプレイヤーに当たったか
	m_touch_collision[1] = GameManager::HitJudgment2(
		touchpos[1] /*- Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2)*/, Vec2(0, 0),
		Vec2(GameManager::PlayerPos.x - GameManager::PlayerSize.x / 2,
			GameManager::PlayerPos.y + GameManager::PlayerSize.y), GameManager::PlayerSize);


	if (m_touch_collision[1] == true && character->isScale == false)
	{
		GameManager::PlayerSize.y = 32;
		character->isScale = true;
		PlaySandWicheSE();
	}


	//タッチ2がプレイヤーに当たったか
	m_touch_collision[1] = GameManager::HitJudgment2(
		touchpos[1] /*- Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2)*/, Vec2(0, 0),
		Vec2(GameManager::PlayerPos.x - GameManager::PlayerSize.x / 2,
			GameManager::PlayerPos.y + GameManager::PlayerSize.y), GameManager::PlayerSize);


	if (m_touch_collision[1] == true && character->isScale == false)
	{
		GameManager::PlayerSize.y = 32;
		character->isScale = true;
		PlaySandWicheSE();

	}

	//タッチ2がプレイヤーに当たったか
	m_touch_collision[1] = GameManager::HitJudgment2(
		touchpos[0]/* - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2)*/, Vec2(0, 0),
		Vec2(GameManager::PlayerPos.x + GameManager::PlayerSize.x / 2,
			GameManager::PlayerPos.y - GameManager::PlayerSize.y), GameManager::PlayerSize);

	if (m_touch_collision[1] == true && character->isScale == false)
	{
				character->isScale = true;

		GameManager::PlayerSize.y = 32;
		PlaySandWicheSE();
	}
	//タッチ2がプレイヤーに当たったか
	m_touch_collision[1] = GameManager::HitJudgment2(
		touchpos[1]/* - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2)*/, Vec2(0, 0),
		Vec2(GameManager::PlayerPos.x + GameManager::PlayerSize.x / 2,
			GameManager::PlayerPos.y - GameManager::PlayerSize.y), GameManager::PlayerSize);

	if (m_touch_collision[1] == true && character->isScale == false)
	{
		character->isScale = true;

		GameManager::PlayerSize.y = 32;
		PlaySandWicheSE();
	}



}



//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//
//概要：金型によるキャラクタの変更
//
//引数：なし
//
//戻り値：なし
//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
void CharacterLayer::ChangeMold()
{
	//前回と違うキャラクタタイプか
	if (old_chara_kind != GameManager::Mold)
	{
		//他のボイスと混ざらないように再生中のボイスを止める
		CharacterVoiceStop();

		switch (GameManager::Mold)
		{
		case GameManager::Normal:
			character->removeFromParent();
			character = Character::create();
			//ノームボイス再生
			m_character_voice[GameManager::Normal] = AudioEngine::play2d("Sounds/domovoice.mp3");
			//変更したので戻す
			GameManager::ChangeMold = false;
			break;
		case GameManager::Rabbit:
			character->removeFromParent();
			character = Rabbit::create();
			//ウサギボイス再生
			m_character_voice[GameManager::Rabbit] = AudioEngine::play2d("Sounds/RabbitVoice.mp3");
			break;
		case GameManager::Gnome:
			//変更したので戻す
			character->removeFromParent();
			character = Gnome::create();
			m_character_voice[GameManager::Gnome] = AudioEngine::play2d("Sounds/Gnome_VoiceSE.mp3");
			break;
		case GameManager::Phoenix:
			//変更したので戻す
			character->removeFromParent();
			character = Phoenix::create();
			m_character_voice[GameManager::Phoenix] = AudioEngine::play2d("Sounds/phoenix_CrySE.mp3");
			break;
		case GameManager::Slime:
			character->removeFromParent();
			character = Slime::create();
			m_character_voice[GameManager::Slime] = AudioEngine::play2d("Sounds/SlimeSE.mp3");
			break;
		case GameManager::Witch:
			character->removeFromParent();
			character = Witch::create();
			m_character_voice[GameManager::Witch] = AudioEngine::play2d("Sounds/Witch.mp3");
		}
		//変更したのでaddChildする
		this->addChild(character);
	}
		//ジャンプ情報をリセットする
		GameManager::JumpCnt = 0;
		GameManager::JumpFlag = true;
		//今回のキャラタイプを保存する
		old_chara_kind = GameManager::Mold;
}





/***************************************************************************
*|	概要　	プレイヤーと床の衝突判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::CollisionResponseFloor()
{
	int hitcnt = 0;
	std::vector<Vec2>::iterator Iterator;
	//////マップの数だけループ
		//床の数だけループ
		for (Iterator = GameManager::AllFloorPos[GameManager::PlayerMapPos].begin(); Iterator != GameManager::AllFloorPos[GameManager::PlayerMapPos].end(); ++Iterator)
		{
			Vec2 vec = *Iterator;
			switch (GameManager::CollisionDetermination
			(vec, GameManager::LAYRE_SIZE,
				GameManager::PlayerPos, GameManager::PlayerSize))
			{
			case GameManager::right:
			
				/*GameManager::PlayerPos.x = vec.x + GameManager::LAYRE_SIZE.x + GameManager::PlayerSize.x / 2 + 1;
				GameManager::PlayerSpd.x = 0.0f;
				hitcnt++;*/
				break;

			case GameManager::left:

				//	ゲームオーバーにする
				GameManager::GameOverFlag = true;

				GameManager::PlayerPos.x = vec.x - GameManager::PlayerSize.x / 2;
				//GameManager::RightFlag = true;
				//GameManager::PlayerSpd.x = -6.0f;
				//当たったので潰れる
				/*character->s_player->setAnchorPoint(Vec2(0, 0));
				GameManager::PlayerSize.x = 32;
				GameManager::PlayerPos.x += 16;*/


				hitcnt++;
				break;
			case GameManager::up:
				GameManager::PlayerPos.y = vec.y;
				GameManager::PlayerSpd.y = 0.0f;
				//ジャンプ可能にする
				GameManager::JumpCnt = 0;
				GameManager::JumpFlag = true;
				hitcnt++;

			//	character->GroundFlag = true;
				break;
				case GameManager::under:
				GameManager::PlayerPos.y = vec.y - GameManager::LAYRE_SIZE.y - GameManager::PlayerSize.y-10;
				GameManager::PlayerSpd.y = 0.0f;
				hitcnt++;
				break;
			default:
				break;

				}
		}	
		
		//複数個所当たっているか
		if (hitcnt > 2)
		{
			//大きさを元に戻す処理を行わない
			character->FloormultipleFlag = true;
		}
		else
		{
			//大きさを元に戻す処理を行う
			character->FloormultipleFlag = false;
		}
}





/***************************************************************************
*|	概要　	ジャンプするか調べる
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::JumpInvestigate()
{

	//最初のタッチフラグが真なら
	if (FirstTouchFlag == true)
	{
		FirstTouchCnt++;
	}
	//一回目のタッチから1秒以上経過したなら

	if (FirstTouchCnt > 6)
	{
		//ジャンプ関数を呼ぶ
		character->Jump();
		//最初のタッチフラグを偽にする
		FirstTouchFlag = false;
		//最初のタッチカウントを初期化する
		FirstTouchCnt = 0;

		GameManager::JumpState = true;
	}
}

/***************************************************************************
*|	概要　	キャラクタボイスを全て止める関数
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CharacterLayer::CharacterVoiceStop()
{
	for (int i = 0; i < GameManager::MaxCharacterKind; i++) /*if (m_character_voice[i] != 0)*/AudioEngine::stop(m_character_voice[i]);
}
