/***************************************************************************
*|
*|	概要　スコアクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "CrayStage.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;


bool CrayStage::init()
{
	if (!Node::init()) {
		return false;
	}

	//レイヤー取得
	TMXLayer* layer2 = GameManager::map[GameManager::MapLoopCnt]->getLayer("CrayFloorLayer");

	bool flag = true;
	CryFloorCnt = 0;
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
					std::string str = properties["Mold"].asString();
					if (str == "Mold")
					{
						cryfloor = Sprite::create("Images/CryFloor.png");
						//アンカーポイントに設定する
						cryfloor->setAnchorPoint(Vec2(0.5f,0.0f));
						//座標を設定する
						cryfloor->
							setPosition(j * GameManager::LAYRE_SIZE.x + (GameManager::LAYRE_SIZE.x* 2) + GameManager::MapLoopCnt * 1920,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y - (GameManager::LAYRE_SIZE.y * 8));

						//粘土床にタグをつける
						cryfloor->setTag(CryFloorCnt);
						this->addChild(cryfloor);
						//粘土床をインクリメント
						CryFloorCnt++;
						//座標を設定する
						CrayStagePos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt * 1920,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y));
					}
				}
			}
		}
	}
	GameManager::AllCrayFloorPos.push_back(CrayStagePos);

	return true;
}


