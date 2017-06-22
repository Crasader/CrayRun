/***************************************************************************
*|
*|	概要　　敵クラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/5/17
*|___________________________________________________________________________
****************************************************************************/

/* ----  インクルード ---------- */
#include "Enemy.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;

/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool Enemy::init()
{
	if (!Node::init()) {

		return false;

	}
	//レイヤー取得
	TMXLayer* layer = GameManager::map[GameManager::MapLoopCnt]->getLayer("EnemyLayer");

	//一回目:レイヤーの数を調べる,2回目:座標を設定する
	for (int i = 0; i < GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y; i++)
	{
		for (int j = 0; j < GameManager::MAP_SIZE.x / GameManager::LAYRE_SIZE.x; j++)
		{
			//タイルの番号
			unsigned int gid = layer->getTileGIDAt(Vec2(j, i));

			// 指定したタイル番号のプロパティのセットを取得
			cocos2d::Value value = GameManager::map[GameManager::MapLoopCnt]->getPropertiesForGID(gid);

			if (value.isNull() == false)
			{
				// 配列として解釈
				cocos2d::ValueMap properties = value.asValueMap();
				if (properties.empty() == false)
				{
					// "type"プロパティを文字列として取得
					std::string str = properties["enemy"].asString();
					if (str == "enemy")
					{
						////座標を設定する
						//m_EnemyPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt * GameManager::MAP_SIZE.x,
						//	(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y));
						//敵を生成、設定
						m_enemy = EnemySprite::create("Images/enemy1.png");
						m_enemy->setScale(2.0 / 3.0f);
						m_enemy->setAnchorPoint(Vec2(0, 1));
						m_enemy->setPosition((Vec2(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt * GameManager::MAP_SIZE.x,
								(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y)));
						this->addChild(m_enemy);
					}
				}
			}
		}
	}
	return true;
}

