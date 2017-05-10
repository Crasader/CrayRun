/***************************************************************************
*|
*|	概要　ステージクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "Stage.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;


bool Stage::init()
{
	if (!Node::init()) {

		return false;

	}
		//レイヤー取得
		TMXLayer* layer = GameManager::map[GameManager::MapLoopCnt]->getLayer("FloorLayer");
		
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
							std::string str = properties["floor"].asString();
							if (str == "floor")
							{
								//座標を設定する
								m_FloorPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt * 1920,
									(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y));
							}
						}
					}
				}
		}
			//今回のループの座標を格納する
			GameManager::AllFloorPos.push_back(m_FloorPos);
	return true;
}


