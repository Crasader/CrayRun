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

	bool flag = true;

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
						switch (Rabbit)
						{
						case Normal:
							m_kind = Normal;
							break;
						case Rabbit:
							m_kind = Rabbit;
							s_Mold = Sprite::create("Images/111.png");
							break;
						case Gnome:
							m_kind = Gnome;
							break;
						case Phoenix:
							m_kind = Phoenix;
							break;
						case Slime:
							m_kind = Slime;
						default:
							break;
						}
					
						s_Mold->setAnchorPoint(Vec2(0, 1));
						//���W��ݒ肷��
						s_Mold->
							setPosition(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt *  GameManager::MAP_SIZE.x,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y);

						//���^�̃A�N�V����
						MoveBy* moldaction = MoveBy::create(1.0f,Vec2(0.0f, 64 * 2.0f));
						MoveBy* moldaction2 = MoveBy::create(1.0f, Vec2(0.0f, -64 * 2.0f));
						Sequence* moldaction3 = Sequence::create(moldaction, moldaction2, nullptr);
						RepeatForever* moldaction4 = RepeatForever::create(moldaction3);
						s_Mold->runAction(moldaction4);

						this->addChild(s_Mold);

						//���̃��[�v�Ń������m�ۂ������Ȃ�
						flag = false;
					}
				}
			}
		}
	}

	return true;
}