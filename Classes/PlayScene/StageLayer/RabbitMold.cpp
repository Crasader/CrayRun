//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//
//　ファイル名：RabbitMold.cpp
//
//	概　　　要：兎型の金型
//
//　作　成　者：GS2 24 山本悠雅
//
//　作　成　日：2017/05/02
//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "RabbitMold.h"

USING_NS_CC;

bool RabbitMold::init() {

	if (!Mold::init()) {

		return false;
	}


	bool flag = true;

	//レイヤー取得
	TMXLayer* layer2 = GameManager::map[GameManager::MapLoopCnt]->getLayer("MoldLayer");

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

						s_Mold = Sprite::create("Images/Rabbit_Model.png");
						s_Mold->setAnchorPoint(Vec2(0, 1));

						//座標を設定する
						s_Mold->
							setPosition(j * GameManager::LAYRE_SIZE.x,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y);

						GameManager::MoldPos.push_back(s_Mold->getPosition());

						s_Mold->setTag(m_MoldCnt);


						this->addChild(s_Mold);


						//床カウントをインクリメント

						m_MoldCnt++;

						this->addChild(s_Mold);

						//次のループでメモリ確保をさせない
						flag = false;
					}
				}
			}
		}
	}
	return true;
}

