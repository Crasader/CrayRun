/***************************************************************************
*|
*|	概要　スコアクラスの定義
*|　作成者　GS2 16 中田湧介,GS2 24 山本悠雅
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "Character.h"


USING_NS_CC;
using namespace cocos2d::experimental;



bool Character::init()
{
	if (!Node::init()) {

		return false;
	}

	//std::string filename = "Images/1.png";
	//if (!Sprite::initWithFile(filename))
	//{

	//	return false;
	//}

	if (s_player == nullptr){
		//プレイヤー作成
		s_player = Sprite::create("Images/1.png");
		s_player->setPosition(GameManager::PlayerPos);
		s_player->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(s_player);

	}else{
		Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/1.png");

		s_player->setTexture(texture);
		s_player->setContentSize(texture->getContentSize());
	}
		
	return true;
}

//Character * Character::create()
//{
//	Character *pRet = new(std::nothrow) Character();
//	if (pRet && pRet->init())
//	{
//		pRet->autorelease();
//		return pRet;
//	}
//	else
//	{
//		delete pRet;
//		pRet = nullptr;
//		return nullptr;
//	}
//}

/***************************************************************************
*|	概要　　移動する
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void Character::Move()
{
	//座標に速度をたす
	GameManager::PlayerPos += GameManager::PlayerSpd;
	//座標を適用させる
	s_player->setPosition(GameManager::PlayerPos);
}

/***************************************************************************
*|	概要　  ジャンプ
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void Character::Jump()
{
	//JumpBy* jumpaction = JumpBy::create(0.5f, Vec2(0,0), 64.0f, 1);
	//s_player->runAction(jumpaction);
	GameManager::JumpCnt++;

	if (GameManager::JumpFlag == true)
	{
		GameManager::PlayerSpd.y = 9.0f;
	}

	if (GameManager::JumpCnt == 2)
	{
		GameManager::JumpCnt = 0;
		GameManager::JumpFlag = false;
	}
}



