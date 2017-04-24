/***************************************************************************
*|
*|	�T�v�@�X�R�A�N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "Stage.h"


USING_NS_CC;


bool Stage::init()
{
	if (!Node::init()) {

		return false;

	}


		s_Sorp = Sprite::create("Images/c.png");
		s_Sorp->setAnchorPoint(Vec2(0, 0));
		s_Sorp->setPosition(Vec2(300, 400));

		this->addChild(s_Sorp);


		//���C���[�擾
		TMXLayer* layer = GameManager::map->getLayer("FloorLayer");
		
		bool flag = true;

		//����:���C���[�̐��𒲂ׂ�,2���:���W��ݒ肷��
			for (int i = 0; i < GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y; i++)
			{
				for (int j = 0; j < GameManager::MAP_SIZE.x / GameManager::LAYRE_SIZE.x; j++)
				{
					//�^�C���̔ԍ�
					unsigned int gid = layer->getTileGIDAt(Vec2(j, i));

					// �w�肵���^�C���ԍ��̃v���p�e�B�̃Z�b�g���擾
					cocos2d::Value value = GameManager::map->getPropertiesForGID(gid);

					if (value.isNull() == false)
					{
						// �z��Ƃ��ĉ���
						cocos2d::ValueMap properties = value.asValueMap();
						if (properties.empty() == false)
						{
							// "type"�v���p�e�B�𕶎���Ƃ��Ď擾
							std::string str = properties["floor"].asString();
							if (str == "floor")
							{


								if (flag == true)
								{


									//���W��ݒ肷��
									GameManager::FloorPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x, GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y);
									//���J�E���g���C���N�������g
									GameManager::FloorCnt++;

									//���̃��[�v�Ń������m�ۂ������Ȃ�
									flag = false;
								}

							}
						}
					}
				}
		}

	return true;
}


