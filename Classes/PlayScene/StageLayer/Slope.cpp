/***************************************************************************
*|
*|	概要　斜面クラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ライブラリのインクルード ---------- */
#include "Slope.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;
bool Slope::init()
{
	if (!Node::init()) {

		return false;
	}

	//レイヤー取得
	TMXLayer* layer = GameManager::map[GameManager::MapLoopCnt]->getLayer("SlopeLayer");
	bool flag = true;
	GameManager::SlopeCnt = 0;

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
						std::string str = properties["Coin"].asString();
						if (str == "coin")
						{
							ClimbingFlag = true;
							if (ClimbingFlag == true)
							{
								//画像を設定する
								s_slope = Sprite::create("Images/Slope.png");
								//スロープのサイズを取得する
								SlopeSize = s_slope->getContentSize();
								//座標を設定する
								m_LeftPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x - SlopeSize.x / 2 + GameManager::LAYRE_SIZE.x / 2 + GameManager::MapLoopCnt * 1920,
									(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y - SlopeSize.y / 2 - GameManager::LAYRE_SIZE.y/2));
								m_RightPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x + SlopeSize.x/2+ GameManager::LAYRE_SIZE.x / 2 + GameManager::MapLoopCnt * 1920,
									(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y + SlopeSize.y / 2 - GameManager::LAYRE_SIZE.y/2));
								//vectorの最初の情報を格納する
								IteratorLeft = m_LeftPos.begin();
								IteratorRight = m_RightPos.begin();
								//イテレータにどこを見るか教える
								IteratorRight += GameManager::SlopeCnt;
								IteratorLeft += GameManager::SlopeCnt;
								//イテレータを格納する
								m_SaveLeft = *IteratorLeft;
								m_SaveRight = *IteratorRight;
								//斜面のスプライトの座標を設定する
								s_slope->setPosition(Vec2(m_SaveLeft.x + SlopeSize.x / 2, 
									m_SaveLeft.y + SlopeSize.y/2));
							}
							//else
							//{
							//	//画像を設定する
							//	s_slope = Sprite::create("Images/Slope.png");
							//	//スロープのサイズを取得する
							//	SlopeSize = s_slope->getContentSize();
							//	//座標を設定する
							//	m_LeftPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x - SlopeSize.x / 2 + GameManager::LAYRE_SIZE.x / 2,
							//		(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y + SlopeSize.y / 2 - GameManager::LAYRE_SIZE.y / 2));
							//	m_RightPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x + SlopeSize.x + SlopeSize.x / 2  +GameManager::LAYRE_SIZE.x / 2, 
							//		(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y - SlopeSize.y / 2 - GameManager::LAYRE_SIZE.y / 2));
							//	//vectorの最初の情報を格納する
							//	IteratorLeft = m_LeftPos.begin();
							//	IteratorRight = m_RightPos.begin();
							//	//イテレータにどこを見るか教える
							//	IteratorRight+= GameManager::SlopeCnt;
							//	IteratorLeft+= GameManager::SlopeCnt;
							//	//イテレータを格納する
							//	m_SaveLeft = *IteratorLeft;
							//	m_SaveLeft = *IteratorRight;
							//	//斜面のスプライトの座標を設定する
							//	s_slope->setPosition(Vec2(m_SaveLeft.x + SlopeSize.x / 2,m_SaveLeft.y - SlopeSize.y / 2));
							//}


							//斜面カウントをインクリメント
							GameManager::SlopeCnt++;
							this->addChild(s_slope);
							//次のループでメモリ確保をさせない
							flag = false;
						}
				}
			}
		}
	}

		//今回のマップ上にある全ての斜面座標を格納する
		GameManager::AllLeftPos.push_back(m_LeftPos);
		GameManager::AllRightPos.push_back(m_RightPos);

	return true;
}


