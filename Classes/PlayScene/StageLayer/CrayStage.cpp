/***************************************************************************
*|
*|	概要　スコアクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "CrayStage.h"

/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;

/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool CrayStage::init()
{
	if (!Node::init()) {
		return false;
	}

	//レイヤー取得
	TMXLayer* layer2 = GameManager::map[GameManager::MapLoopCnt]->getLayer("MapLayer");

	bool flag = true;
	int loop_cnt = 0;
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
					std::string str = properties["crayfloor"].asString();
					if (str == "crayfloor")
					{

						//粘土床を作成
						m_crayfloor.push_back( CrayStageSprite::create("Images/CryFloor.png"));
						//アンカーポイントに設定する
						m_crayfloor[loop_cnt]->setAnchorPoint(Vec2(0.0f, 0.0f));
						//座標を設定する
						m_crayfloor[loop_cnt]->
							setPosition(j * GameManager::LAYRE_SIZE.x + /*(GameManager::LAYRE_SIZE.x*2)*/ +GameManager::MapLoopCnt * GameManager::MAP_SIZE.x,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y - (GameManager::LAYRE_SIZE.y * 4));
					

						this->addChild(m_crayfloor[loop_cnt]);

						////サイズを設定する
						//m_crayfloor->setScale(m_crayfloor->m_size.x, m_crayfloor->m_size.y);
						loop_cnt++;
					}
				}
			}
		}
	}

	return true;
}


