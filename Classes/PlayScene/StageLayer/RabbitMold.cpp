//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//
//�@�t�@�C�����FRabbitMold.cpp
//
//	�T�@�@�@�v�F�e�^�̋��^
//
//�@��@���@�ҁFGS2 24 �R�{�I��
//
//�@��@���@���F2017/05/02
//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "RabbitMold.h"

USING_NS_CC;

bool RabbitMold::init() {

	if (!Mold::init()) {

		return false;
	}


	bool flag = true;

	//���C���[�擾
	TMXLayer* layer2 = GameManager::map[GameManager::MapLoopCnt]->getLayer("MoldLayer");

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
					std::string str = properties["Mold"].asString();
					if (str == "Mold")
					{

						s_Mold = Sprite::create("Images/Rabbit_Model.png");
						s_Mold->setAnchorPoint(Vec2(0, 1));

						//���W��ݒ肷��
						s_Mold->
							setPosition(j * GameManager::LAYRE_SIZE.x,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y);

						GameManager::MoldPos.push_back(s_Mold->getPosition());

						s_Mold->setTag(m_MoldCnt);


						this->addChild(s_Mold);


						//���J�E���g���C���N�������g

						m_MoldCnt++;

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

