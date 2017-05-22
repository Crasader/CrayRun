//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//
//　ファイル名：Mold.cpp
//
//	概　　　要：金型(基底クラス)
//
//　作　成　者：GS2 24 山本悠雅
//
//　作　成　日：2017/05/02
//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "Mold.h"

USING_NS_CC;

bool Mold::init(){

	if (!Node::init()) {

		return false;
	}

	int loop_cnt = 0;

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
					std::string str = properties["mold"].asString();
					if (str == "mold")
					{
						//ランダムでキャラクターを作成する
						switch (rand() % 4 + 1)
						{

						case Rabbit:
							m_kind.push_back(Rabbit);
							s_Mold.push_back(Sprite::create("Images/Rabbit_Model.png"));
							break;
						case Gnome:
							m_kind.push_back(Gnome);
							s_Mold.push_back(Sprite::create("Images/Gnome_Chara.png"));
							break;
						case Phoenix:
							m_kind.push_back(Phoenix);
							s_Mold.push_back(Sprite::create("Images/Phoenix_Chara.png"));
							break;
						case Slime:
							m_kind.push_back(Slime);
							s_Mold.push_back(Sprite::create("Images/slime_Mold.png"));
							break;
						default:
							break;
						}


						s_Mold[loop_cnt]->setAnchorPoint(Vec2(0, 1));
						//座標を設定する
						s_Mold[loop_cnt]->
							setPosition(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt *  GameManager::MAP_SIZE.x,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y);

						//金型のアクション
						MoveBy* moldaction = MoveBy::create(1.0f,Vec2(0.0f, 64 * 2.0f));
						MoveBy* moldaction2 = MoveBy::create(1.0f, Vec2(0.0f, -64 * 2.0f));
						Sequence* moldaction3 = Sequence::create(moldaction, moldaction2, nullptr);
						RepeatForever* moldaction4 = RepeatForever::create(moldaction3);
						s_Mold[loop_cnt]->runAction(moldaction4);


						this->addChild(s_Mold[loop_cnt]);
						//カウントを増やす
						loop_cnt++;
					}
				}
			}
		}
	}

	return true;
}