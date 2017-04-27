/***************************************************************************
*|
*|	概要　斜面クラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "Slope.h"


USING_NS_CC;

bool Slope::init()
{
	if (!Node::init()) {

		return false;
	}
	//IteratorLeft = GameManager::LeftPos.begin();
	//IteratorRight = GameManager::RightPos.begin();

	////レイヤー取得
	//TMXLayer* layer = GameManager::map->getLayer("SlopeLayer");

	//bool flag = true;

	//	for (int i = 0; i < GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y; i++)
	//	{
	//		for (int j = 0; j < GameManager::MAP_SIZE.x / GameManager::LAYRE_SIZE.x; j++)
	//		{
	//			//タイルの番号
	//			unsigned int gid = layer->getTileGIDAt(Vec2(j, i));

	//			// 指定したタイル番号のプロパティのセットを取得
	//			cocos2d::Value value = GameManager::map->getPropertiesForGID(gid);

	//			if (value.isNull() == false)
	//			{
	//				// 配列として解釈
	//				cocos2d::ValueMap properties = value.asValueMap();
	//				if (properties.empty() == false)
	//				{
	//					// "type"プロパティを文字列として取得
	//					std::string str = properties["Coin"].asString();
	//					if (str == "coin")
	//					{
	//						 ClimbingFlag = rand() %2;

	//						if (ClimbingFlag == true)
	//						{
	//							s_slope = Sprite::create("Slope.png");
	//							//スロープのサイズを取得する
	//							SlopeSize = s_slope->getContentSize();
	//							//座標を設定する
	//							GameManager::LeftPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x - SlopeSize.x / 2, (GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y - SlopeSize.y / 2));
	//							GameManager::RightPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x + SlopeSize.x + SlopeSize.x / 2, (GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y + SlopeSize.y / 2));
	//							s_slope->setPosition(Vec2(GameManager::SaveLeft.x + SlopeSize.x / 2, GameManager::SaveLeft.y + SlopeSize.y));
	//						}
	//						else
	//						{
	//							s_slope = Sprite::create("Slope.png");
	//							//スロープのサイズを取得する
	//							SlopeSize = s_slope->getContentSize();
	//							//座標を設定する
	//							GameManager::LeftPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x - SlopeSize.x / 2, (GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y + SlopeSize.y / 2));
	//							GameManager::RightPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x + SlopeSize.x + SlopeSize.x / 2, (GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y - SlopeSize.y / 2));
	//							s_slope->setPosition(Vec2(GameManager::SaveLeft.x + SlopeSize.x / 2, GameManager::SaveLeft.y - SlopeSize.y / 2));


	//						}
	//						

	//							//setPosition(j * GameManager::LAYRE_SIZE.x,
	//							//(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y);

	//						
	//						//イテレータを格納する
	//						GameManager::SaveLeft = *IteratorLeft;
	//						GameManager::SaveRight = *IteratorRight;
	//						
	//						

	//						

	//						this->addChild(s_slope);


	//						//イテレータをインクリメント
	//						IteratorRight++;
	//						IteratorLeft++;


	//						//次のループでメモリ確保をさせない
	//						flag = false;
	//					}
	//			}
	//		}
	//	}
	//}



	return true;
}


