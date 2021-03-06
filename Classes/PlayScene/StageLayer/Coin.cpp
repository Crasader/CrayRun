/***************************************************************************
*|
*|	概要　コインクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "Coin.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;

/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool Coin::init()
{
	if (!Node::init()) {

		return false;
	}


	//レイヤー取得
	TMXLayer* layer2 = GameManager::map[GameManager::MapLoopCnt]->getLayer("MapLayer");

	//一回目:レイヤーの数を調べる,2回目:座標を設定する
	for (int i = 0; i < GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y; i++)
	{
		for (int j = 0; j < GameManager::MAP_SIZE.x / GameManager::LAYRE_SIZE.x; j++)
		{
			//タイルの番号
			unsigned int gid = layer2->getTileGIDAt(Vec2(j, i));

			// 指定したタイル番号のプロパティのセットを取得
			cocos2d::Value value = GameManager::map[GameManager::MapLoopCnt]->getPropertiesForGID(gid);

			if (value.isNull() == false)
			{
				// 配列として解釈
				cocos2d::ValueMap properties = value.asValueMap();
				if (properties.empty() == false)
				{
					// "type"プロパティを文字列として取得
					std::string str = properties["coin"].asString();
					if (str == "coin")
					{
						//画像をランダムで設定する
						switch (rand() % 3 + 1)
						{
						case 1:
							s_Coin = CoinSprite::create("Images/coin1.png",10);
							break;
						case 2:
							s_Coin = CoinSprite::create("Images/Coin2.png",20);
						case 3:
							s_Coin = CoinSprite::create("Images/Coin3.png",30);
							break;
							break;
						}
						//座標を設定する
						s_Coin->
							setPosition(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt * GameManager::MAP_SIZE.x + GameManager::LAYRE_SIZE.x / 2,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y - GameManager::LAYRE_SIZE.y / 2);
						this->addChild(s_Coin ,-100);
					

					}
				}
			}
		}
		
	}
	return true;
}


