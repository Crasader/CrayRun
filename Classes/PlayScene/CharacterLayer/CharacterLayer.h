/***************************************************************************
*|
*|	概要　　キャラクターレイヤーの宣言
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- 多重インクルードの防止 ---------- */
#pragma once 
/* ----  インクルード ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"
#include "Character.h"
#include "Rabbit.h"
#include "Slime.h"
#include "Gnome.h"
#include "Phoenix.h"
#include "Witch.h"
#include "audio/include/AudioEngine.h"

//有効なタッチの数
 const int EFFECTIVENESS_TOUCH = 2;
class CharacterLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(CharacterLayer);
	//キャラクターオブジェクト
	Character* character;



private:


	//毎フレーム呼び出される関数
	void update(float delta)override;
	//タッチ時に呼び出される
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//スワイプ時に呼び出される
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//タッチが離された
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//タッチ異常終了
	void onTouchesCancelled(const std::vector<cocos2d::Touch*>&touches, cocos2d::Event *unused_event);

	//キャラクターのマルチタッチ判定
	void  MultiTouchCharacter();


	//金型の変更
	void ChangeMold();
	//プレイヤーとステージのあたり判定
	void CollisionResponseFloor();
	//ジャンプするか調べる
	void JumpInvestigate();

	//タッチID格納
	int m_touch_id;
	
	//タッチ座標
	cocos2d::Vec2 touchpos[EFFECTIVENESS_TOUCH];

	//タッチサイズ
	const cocos2d::Vec2 TOUCH_SIZE = cocos2d::Vec2(96,96);
	int FirstTouchCnt;//最初のタッチからどれだけ経過したか
	bool FirstTouchFlag = false;//最初のタッチが呼ばれたか

	//最初の座標
	cocos2d::Vec2 FirstPos[EFFECTIVENESS_TOUCH];
	

	int FirstMultiTouchFlag;


	//前回のキャラクタタイプ
	GameManager::CharacterKind old_chara_kind;


	//キャラクタのボイス
	int m_character_voice[GameManager::MaxCharacterKind];
	//挟まれるボイス
	int m_SandWicheSE;

	//挟まれるボイス再生
	void PlaySandWicheSE() {
		if (m_SandWicheSE == 0)
		{
			m_SandWicheSE = cocos2d::experimental::AudioEngine::play2d("Sounds/Interpose.mp3");
		}
	}
	//キャラクタボイスを全て止める関数
	void CharacterVoiceStop();
};

