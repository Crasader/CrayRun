/***************************************************************************
*|
*|	概要　コインクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "Coin.h"


USING_NS_CC;

bool Coin::init()
{
	if (!Node::init()) {

		return false;
	}

	//レイヤー取得
	TMXLayer* layer2 = GameManager::map->getLayer("CoinLayer");

	bool flag = true;

	//一回目:レイヤーの数を調べる,2回目:座標を設定する
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y; i++)
		{
			for (int j = 0; j < GameManager::MAP_SIZE.x / GameManager::LAYRE_SIZE.x; j++)
			{
				//タイルの番号
				unsigned int gid = layer2->getTileGIDAt(Vec2(j, i));

				// 指定したタイル番号のプロパティのセットを取得
				cocos2d::Value value = GameManager::map->getPropertiesForGID(gid);

				if (value.isNull() == false)
				{
					// 配列として解釈
					cocos2d::ValueMap properties = value.asValueMap();
					if (properties.empty() == false)
					{
						// "type"プロパティを文字列として取得
						std::string str = properties["Coin"].asString();
						if (str == "coin")
						{

							//画像をランダムで設定する
							switch (rand() % 3 + 1)
							{
							case 1:
								s_Coin = Sprite::create("Images/coin1.png");
								break;
							case 2:
								s_Coin = Sprite::create("Images/Coin2.png");
							case 3:
								s_Coin = Sprite::create("Images/Coin3.png");
								break;
							default:
								break;
							}
							//座標を設定する
							s_Coin->
								setPosition(j * GameManager::LAYRE_SIZE.x,
								(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y);

							s_Coin->setTag(GameManager::CoinCnt);

							this->addChild(s_Coin);

							//床カウントをインクリメント
							GameManager::CoinCnt++;

							//次のループでメモリ確保をさせない
							flag = false;
						}
					}
				}
			}
		}
	}


	return true;
}


