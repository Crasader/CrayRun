/***************************************************************************
*|
*|	概要　　金型クラスを定義する
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/6/1
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "Mold.h"
/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;


/***************************************************************************
*|	概要　　初期化処理
*|	引数　　無し
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
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
							s_BackMold.push_back (Sprite::create("Images/Rabbit_Model.png"));
							break;

						case Gnome:
							m_kind.push_back(Gnome);
							s_Mold.push_back(Sprite::create("Images/Gnome_Mold.png"));
							s_BackMold.push_back( Sprite::create("Images/Gnome_Mold.png"));
							break;

						case Phoenix:
							m_kind.push_back(Phoenix);
							s_Mold.push_back(Sprite::create("Images/Phoenix_Mold.png"));
							s_BackMold.push_back(Sprite::create("Images/Phoenix_Mold.png"));
							break;

						case Slime:
							m_kind.push_back(Slime);
							s_Mold.push_back(Sprite::create("Images/slime_Mold.png"));
							s_BackMold.push_back(Sprite::create("Images/slime_Mold.png"));
							break;

						default:
							break;
						}
						//手前の金型
						s_Mold[loop_cnt]->setAnchorPoint(Vec2(1, 0.5));
						s_Mold[loop_cnt]->setScale(1.4, 1.4);
						//座標を設定する
						s_Mold[loop_cnt]->
							setPosition(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt *  GameManager::MAP_SIZE.x,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y);

						//描画優先順位を設定する
						s_Mold[loop_cnt]->setGlobalZOrder(100.0f);
						this->addChild(s_Mold[loop_cnt]);


						//奥の金型
						s_BackMold[loop_cnt]->setColor(Color3B(100, 100, 100));
						s_BackMold[loop_cnt]->setAnchorPoint(Vec2(1, 0.5));
						s_BackMold[loop_cnt]->setScale(1.0f, 1.0f);
						s_BackMold[loop_cnt]->
							setPosition(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt *  GameManager::MAP_SIZE.x + m_while_distance,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y);
						this->addChild(s_BackMold[loop_cnt]);



						////金型のアクション
						//MoveBy* moldaction = MoveBy::create(1.0f, Vec2(0.0f, 64 * 2.0f));
						//MoveBy* moldaction2 = MoveBy::create(1.0f, Vec2(0.0f, -64 * 2.0f));
						//Sequence* moldaction3 = Sequence::create(moldaction, moldaction2, nullptr);
						//RepeatForever* moldaction4 = RepeatForever::create(moldaction3);

						////金型のアクション
						//MoveBy* moldaction0 = MoveBy::create(1.0f, Vec2(0.0f, 64 * 2.0f));
						//MoveBy* moldaction02 = MoveBy::create(1.0f, Vec2(0.0f, -64 * 2.0f));
						//Sequence* moldaction03 = Sequence::create(moldaction0, moldaction02, nullptr);
						//RepeatForever* moldaction04 = RepeatForever::create(moldaction03);

						////アクションを実行
						//s_Mold[loop_cnt]->runAction(moldaction4);
						//s_BackMold[loop_cnt]->runAction(moldaction04);

					
						//カウントを増やす
						loop_cnt++;
					}
				}
			}
		}
	}

	return true;
}