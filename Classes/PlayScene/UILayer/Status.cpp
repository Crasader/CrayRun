/***************************************************************************
*|
*|	概要　　ステータスクラスを定義する
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/6/1
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "Status.h"
/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;


/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool Status::init()
{
	//ノードの作成に失敗したらfalseを返す
	if (!Node::init())
	{
		return false;
	}

	s_status[GameManager::Normal] = Sprite::create("Images/Player_status .png");
	s_status[GameManager::Rabbit] = Sprite::create("Images/Rabbit_status.png");
	s_status[GameManager::Gnome] = Sprite::create("Images/Gnome_status.png");
	s_status[GameManager::Phoenix] = Sprite::create("Images/Phoenix_status.png");
	s_status[GameManager::Slime] = Sprite::create("Images/Slime_status.png");
	s_status[GameManager::Witch] = Sprite::create("Images/Witch_status.png");


	for (int i = 0; i < GameManager::MaxCharacterKind; i++)
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
	for (int i = 0; i < GameManager::MaxCharacterKind; i++)
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
	for (int i = 0; i < GameManager::MaxCharacterKind; i++)
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
	case GameManager::Normal:
		s_status[GameManager::Normal]->runAction(m_status_action);
		break;
	case GameManager::Rabbit:
		s_status[GameManager::Rabbit]->runAction(m_status_action);
		break;
	case GameManager::Gnome:
		s_status[GameManager::Gnome]->runAction(m_status_action);
		break;
	case GameManager::Phoenix:
		s_status[GameManager::Phoenix]->runAction(m_status_action);
		break;
	case GameManager::Slime:
		s_status[GameManager::Slime]->runAction(m_status_action);
		break;
	case GameManager::Witch:
		s_status[GameManager::Witch]->runAction(m_status_action);
		break;
	}






}
