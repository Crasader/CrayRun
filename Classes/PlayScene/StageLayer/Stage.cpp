/***************************************************************************
*|
*|	概要　スコアクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "Stage.h"


USING_NS_CC;


bool Stage::init()
{
	if (!Node::init()) {

		return false;

	}


		s_Sorp = Sprite::create("Images/c.png");
		s_Sorp->setAnchorPoint(Vec2(0, 0));
		s_Sorp->setPosition(Vec2(300, 400));

		this->addChild(s_Sorp);


		/////////マップ描画////////

		//タイルマップの読み込み
		//マップチップ
		TMXTiledMap*  map = TMXTiledMap::create("floor.tmx");
		//タイルマップの中心座標を設定
		map->setAnchorPoint(Vec2(0, 0));
		//タイルマップの座標設定
		map->setPosition(Point(0, 0));
		//画像の描画
		this->addChild(map);
		//レイヤー取得
		TMXLayer* layer = map->getLayer("FloorLayer");

		bool flag = true;

		//一回目:レイヤーの数を調べる,2回目:座標を設定する
		for (int k = 0; k < 2; k++)
		{
			for (int i = 0; i < GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y; i++)
			{
				for (int j = 0; j < GameManager::MAP_SIZE.x / GameManager::LAYRE_SIZE.x; j++)
				{
					//タイルの番号
					unsigned int gid = layer->getTileGIDAt(Vec2(j, i));

					// 指定したタイル番号のプロパティのセットを取得
					cocos2d::Value value = map->getPropertiesForGID(gid);

					if (value.isNull() == false)
					{
						// 配列として解釈
						cocos2d::ValueMap properties = value.asValueMap();
						if (properties.empty() == false)
						{
							// "type"プロパティを文字列として取得
							std::string str = properties["floor"].asString();
							if (str == "floor")
							{

								if (k == 0)
								{
									//床カウントをインクリメント
									GameManager::FloorCnt++;
								}
								else if (flag == true)
								{
									//動的に配列を作成
									GameManager::FloorPosx = new float[GameManager::FloorCnt];
									//動的に配列を作成
									GameManager::FloorPosy = new float[GameManager::FloorCnt];

									//床の数を初期化する
									GameManager::FloorCnt = 0;

									//座標を設定する
									GameManager::FloorPosx[GameManager::FloorCnt] = j * GameManager::LAYRE_SIZE.x;
									GameManager::FloorPosy[GameManager::FloorCnt] = (GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y;
									//床カウントをインクリメント
									GameManager::FloorCnt++;

									//次のループでメモリ確保をさせない
									flag = false;
								}
								else
								{
									//座標を設定する
									GameManager::FloorPosx[GameManager::FloorCnt] = j * GameManager::LAYRE_SIZE.x;
									GameManager::FloorPosy[GameManager::FloorCnt] = (GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y;
									//床カウントをインクリメント
									GameManager::FloorCnt++;
								}
							}
						}
					}
				}
			}
		}

	return true;
}


