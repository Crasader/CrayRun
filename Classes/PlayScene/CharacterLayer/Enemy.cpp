/***************************************************************************
*|
*|	概要　ステージクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "Enemy.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;


bool Enemy::init()
{
	if (!Node::init()) {

		return false;

	}
	//レイヤー取得
	TMXLayer* layer = GameManager::map[GameManager::MapLoopCnt]->getLayer("EnemyLayer");

	m_loopcnt = 0;
	m_animecnt = 0;
	bool flag = true;

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
						//座標を設定する
						m_EnemyPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt * GameManager::MAP_SIZE.x,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y));

						s_enemy.push_back(Sprite::create("Images/enemy1.png"));
						s_enemy[m_loopcnt]->setScale(2.0 / 3.0f);
						s_enemy[m_loopcnt]->setAnchorPoint(Vec2(0,1));
						s_enemy[m_loopcnt]->setPosition(m_EnemyPos[m_loopcnt]);
						this->addChild(s_enemy[m_loopcnt]);

						m_loopcnt++;
					}
				}
			}
		}
	}

	return true;
}

void Enemy::update(float delta)
{
	if (m_animecnt % 7 == 0)
	{
		Texture2D* texture;
		for (int i = 0; i < m_loopcnt; i++)
		{
			switch (m_animecnt / 7 % 6)
			{
			case 0:
			case 5:
				texture = TextureCache::sharedTextureCache()->addImage("Images/enemy1.png");

				s_enemy[i]->setTexture(texture);
				break;
			case 1:
			case 4:
				texture = TextureCache::sharedTextureCache()->addImage("Images/enemy3.png");

				s_enemy[i]->setTexture(texture);
				break;

			case 2:
			case 3:

				texture = TextureCache::sharedTextureCache()->addImage("Images/enemy2.png");

				s_enemy[i]->setTexture(texture);
				break;
			default:
				break;
			}
		}
	}
	m_animecnt++;
}


