//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//
//�@�t�@�C�����FMold.cpp
//
//	�T�@�@�@�v�F���^(���N���X)
//
//�@��@���@�ҁFGS2 24 �R�{�I��
//
//�@��@���@���F2017/05/02
//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "Mold.h"

USING_NS_CC;

bool Mold::init(){

	if (!Node::init()) {

		return false;
	}

	int loop_cnt = 0;

	//���C���[�擾
	TMXLayer* layer2 = GameManager::map[GameManager::MapLoopCnt]->getLayer("MapLayer");

	//����:���C���[�̐��𒲂ׂ�,2���:���W��ݒ肷��
	for (int i = 0; i < GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y; i++)
	{
		for (int j = 0; j < GameManager::MAP_SIZE.x / GameManager::LAYRE_SIZE.x; j++)
		{
			//�^�C���̔ԍ�
			unsigned int gid = layer2->getTileGIDAt(Vec2(j, i));

			// �w�肵���^�C���ԍ��̃v���p�e�B�̃Z�b�g���擾
			cocos2d::Value value = GameManager::map[GameManager::MapLoopCnt]->getPropertiesForGID(gid);

			if (value.isNull() == false)
			{
				// �z��Ƃ��ĉ���
				cocos2d::ValueMap properties = value.asValueMap();
				if (properties.empty() == false)
				{
					// "type"�v���p�e�B�𕶎���Ƃ��Ď擾
					std::string str = properties["mold"].asString();
					if (str == "mold")
					{
						//�����_���ŃL�����N�^�[���쐬����
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
						//��O�̋��^
						s_Mold[loop_cnt]->setAnchorPoint(Vec2(1, 0.5));
						s_Mold[loop_cnt]->setScale(1.8, 1.8);
						//���W��ݒ肷��
						s_Mold[loop_cnt]->
							setPosition(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt *  GameManager::MAP_SIZE.x,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y);

						//�`��D�揇�ʂ�ݒ肷��
						s_Mold[loop_cnt]->setGlobalZOrder(100.0f);
						this->addChild(s_Mold[loop_cnt]);


						//���̋��^
						s_BackMold[loop_cnt]->setAnchorPoint(Vec2(1, 0.5));
						s_BackMold[loop_cnt]->setScale(1.2f, 1.2f);
						s_BackMold[loop_cnt]->
							setPosition(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt *  GameManager::MAP_SIZE.x + m_while_distance,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y);
						this->addChild(s_BackMold[loop_cnt]);



						////���^�̃A�N�V����
						//MoveBy* moldaction = MoveBy::create(1.0f, Vec2(0.0f, 64 * 2.0f));
						//MoveBy* moldaction2 = MoveBy::create(1.0f, Vec2(0.0f, -64 * 2.0f));
						//Sequence* moldaction3 = Sequence::create(moldaction, moldaction2, nullptr);
						//RepeatForever* moldaction4 = RepeatForever::create(moldaction3);

						////���^�̃A�N�V����
						//MoveBy* moldaction0 = MoveBy::create(1.0f, Vec2(0.0f, 64 * 2.0f));
						//MoveBy* moldaction02 = MoveBy::create(1.0f, Vec2(0.0f, -64 * 2.0f));
						//Sequence* moldaction03 = Sequence::create(moldaction0, moldaction02, nullptr);
						//RepeatForever* moldaction04 = RepeatForever::create(moldaction03);

						////�A�N�V���������s
						//s_Mold[loop_cnt]->runAction(moldaction4);
						//s_BackMold[loop_cnt]->runAction(moldaction04);

					
						//�J�E���g�𑝂₷
						loop_cnt++;
					}
				}
			}
		}
	}

	return true;
}