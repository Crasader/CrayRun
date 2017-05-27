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

	s_status[Rabbit] = Sprite::create("Images/Rabbit_status.png");
	s_status[Gnome] = Sprite::create("Images/Gnome_status.png");
	s_status[Phoenix] = Sprite::create("Images/Phoenix_status.png");
	s_status[Slime] = Sprite::create("Images/Slime_status.png");


	for (int i = 1; i < 5; i++)
	{
		s_status[i]->setScale(1.2f);
		s_status[i]->setPosition(Vec2(GameManager::PlayerPos.x - 140, 200.0f));
		s_status[i]->setVisible(false);
		this->addChild(s_status[i]);
	}
	//
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
	for (int i = 1; i < 5; i++)
	{
		s_status[i]->setPositionY(GameManager::PlayerPos.y
		+ GameManager::PlayerSize.y / 2);
	}
}
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//概要：スプライトの生成
//引数：なし
//戻り値：なし
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
void Status::StatusAction()
{
	//アクションが終わっているか
	for (int i = 1; i < 5; i++)
	{
		if (!s_status[i]->getActionByTag(1))
		{
			s_status[i]->stopActionByTag(1);
		}
		//非表示にする
		s_status[i]->setVisible(false);
	}
	//アクション
	Show* action1 = Show::create();
	DelayTime* action2 = DelayTime::create(5.0f);
	Hide* action3 = Hide::create();
	Sequence* m_status_action = Sequence::create(action1,action2,action3,nullptr);
	m_status_action->setTag(1);


	switch (GameManager::Mold)
	{
	case Normal:
		break;
	case Rabbit:
		s_status[Rabbit]->runAction(m_status_action);
		break;
	case Gnome:
		s_status[Gnome]->runAction(m_status_action);
		break;
	case Phoenix:
		s_status[Phoenix]->runAction(m_status_action);
		break;
	case Slime:
		s_status[Slime]->runAction(m_status_action);
		break;
	}






}
