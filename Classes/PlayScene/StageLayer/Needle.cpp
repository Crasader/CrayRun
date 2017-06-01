/***************************************************************************
*|
*|	概要　　針クラスを定義する
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/6/1
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "Needle.h"
/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;


/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool Needle::init() {

	if (!Node::init()) {

		return false;
	}

	m_needle_cnt = 0;
	//レイヤー取得
	TMXLayer* layer = GameManager::map[GameManager::MapLoopCnt]->getLayer("MapLayer");

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
					std::string str = properties["needle"].asString();
					if (str == "needle")
					{
						//座標を設定する
						s_needle.push_back(Sprite::create("Images/needle.png"));
						//m_iterator_needle = s_needle.begin();
						s_needle[m_needle_cnt]->setPosition(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt *  GameManager::MAP_SIZE.x + GameManager::LAYRE_SIZE.x / 2,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y - GameManager::LAYRE_SIZE.y / 2);
						this->addChild(s_needle[m_needle_cnt]);
						//針の状態を真にする
						m_needle_state.push_back(true);
					
						//何個目かカウント
						m_needle_cnt++;
					}
				}
			}
		}
	}
	return true;
}