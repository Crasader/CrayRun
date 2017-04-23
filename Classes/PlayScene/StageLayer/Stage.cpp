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


		/////////�}�b�v�`��////////

		//�^�C���}�b�v�̓ǂݍ���
		//�}�b�v�`�b�v
		TMXTiledMap*  map = TMXTiledMap::create("floor.tmx");
		//�^�C���}�b�v�̒��S���W��ݒ�
		map->setAnchorPoint(Vec2(0, 0));
		//�^�C���}�b�v�̍��W�ݒ�
		map->setPosition(Point(0, 0));
		//�摜�̕`��
		this->addChild(map);
		//���C���[�擾
		TMXLayer* layer = map->getLayer("FloorLayer");

		bool flag = true;

		//����:���C���[�̐��𒲂ׂ�,2���:���W��ݒ肷��
		for (int k = 0; k < 2; k++)
		{
			for (int i = 0; i < GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y; i++)
			{
				for (int j = 0; j < GameManager::MAP_SIZE.x / GameManager::LAYRE_SIZE.x; j++)
				{
					//�^�C���̔ԍ�
					unsigned int gid = layer->getTileGIDAt(Vec2(j, i));

					// �w�肵���^�C���ԍ��̃v���p�e�B�̃Z�b�g���擾
					cocos2d::Value value = map->getPropertiesForGID(gid);

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

								if (k == 0)
								{
									//���J�E���g���C���N�������g
									GameManager::FloorCnt++;
								}
								else if (flag == true)
								{
									//���I�ɔz����쐬
									GameManager::FloorPosx = new float[GameManager::FloorCnt];
									//���I�ɔz����쐬
									GameManager::FloorPosy = new float[GameManager::FloorCnt];

									//���̐�������������
									GameManager::FloorCnt = 0;

									//���W��ݒ肷��
									GameManager::FloorPosx[GameManager::FloorCnt] = j * GameManager::LAYRE_SIZE.x;
									GameManager::FloorPosy[GameManager::FloorCnt] = (GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y;
									//���J�E���g���C���N�������g
									GameManager::FloorCnt++;

									//���̃��[�v�Ń������m�ۂ������Ȃ�
									flag = false;
								}
								else
								{
									//���W��ݒ肷��
									GameManager::FloorPosx[GameManager::FloorCnt] = j * GameManager::LAYRE_SIZE.x;
									GameManager::FloorPosy[GameManager::FloorCnt] = (GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y;
									//���J�E���g���C���N�������g
									GameManager::FloorCnt++;
								}
							}
						}
					}
				}
			}
		}

	return true;
}


