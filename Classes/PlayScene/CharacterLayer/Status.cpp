#include "Status.h"
/// <summary>
/// 概　要：ステータスの定義
/// 作成者：GS2 24 山本悠雅
/// 作成日：2017/05/18
/// </summary>

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

bool Status::init()
{
	//ノードの作成に失敗したらfalseを返す
	if (!Node::init())
	{
		return false;
	}

	//スプライトの生成
	CreateSprite();


	//毎フレーム呼び出す
	this->scheduleUpdate();

	return true;
}

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//概要：更新処理
//引数：なし
//戻り値：なし
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
void Status::update(float delta)
{
	//表示してから5秒経過していないなら
	if (m_cnt < 300)
	{
		Vec2 pos = s_status->getPosition();
		pos.x += GameManager::m_cameraspdx;
		s_status->setPosition(pos);
	}
	else
	{
		RemoveSelf* deleteSprite = RemoveSelf::create();

		this->runAction(deleteSprite);
	}

	m_cnt++;
}
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//概要：スプライトの生成
//引数：なし
//戻り値：なし
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
void Status::CreateSprite()
{
	switch (GameManager::Mold)
	{
	case Normal:
		break;
	case Rabbit:
		s_status = Sprite::create("Images/Rabbit_status.png");
		break;
	case Gnome:
		s_status = Sprite::create("Images/Gnome_status.png");
		break;
	case Phoenix:
		s_status = Sprite::create("Images/Phoenix_status.png");
		break;
	case Slime:
		s_status = Sprite::create("Images/Slime_status.png");
		break;
	}
	s_status->setScale(1.2f);
	s_status->setPosition(Vec2(GameManager::PlayerPos.x - 96.0f, 200.0f));
	this->addChild(s_status);
}
