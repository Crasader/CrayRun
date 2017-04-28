/***************************************************************************
*|
*|	�T�v�@�ΖʃN���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "Slope.h"


USING_NS_CC;
bool Slope::init()
{
	if (!Node::init()) {

		return false;
	}

	//������
	SlopeCnt = 0;

	//���C���[�擾
	TMXLayer* layer = GameManager::map->getLayer("SlopeLayer");
	bool flag = true;

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
						std::string str = properties["Coin"].asString();
						if (str == "coin")
						{/*
							 ClimbingFlag = rand() %2;*/
							ClimbingFlag = true;
							if (ClimbingFlag == true)
							{
								//�摜��ݒ肷��
								s_slope = Sprite::create("Images/Slope.png");
								//�X���[�v�̃T�C�Y���擾����
								SlopeSize = s_slope->getContentSize();
								//���W��ݒ肷��
								GameManager::LeftPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x - SlopeSize.x / 2 + GameManager::LAYRE_SIZE.x / 2, 
									(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y - SlopeSize.y / 2 - GameManager::LAYRE_SIZE.y/2));
								GameManager::RightPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x + SlopeSize.x/2+ GameManager::LAYRE_SIZE.x / 2,
									(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y + SlopeSize.y / 2 - GameManager::LAYRE_SIZE.y/2));
								//vector�̍ŏ��̏����i�[����
								IteratorLeft = GameManager::LeftPos.begin();
								IteratorRight = GameManager::RightPos.begin();
								//�C�e���[�^�ɂǂ������邩������
								IteratorRight += SlopeCnt;
								IteratorLeft += SlopeCnt;
								//�C�e���[�^���i�[����
								GameManager::SaveLeft = *IteratorLeft;
								GameManager::SaveRight = *IteratorRight;
								//�Ζʂ̃X�v���C�g�̍��W��ݒ肷��
								s_slope->setPosition(Vec2(GameManager::SaveLeft.x + SlopeSize.x / 2, GameManager::SaveLeft.y + SlopeSize.y/2));
							}
							else
							{
								//�摜��ݒ肷��
								s_slope = Sprite::create("Images/Slope.png");
								//�X���[�v�̃T�C�Y���擾����
								SlopeSize = s_slope->getContentSize();
								//���W��ݒ肷��
								GameManager::LeftPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x - SlopeSize.x / 2 + GameManager::LAYRE_SIZE.x / 2,
									(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y + SlopeSize.y / 2 - GameManager::LAYRE_SIZE.y / 2));
								GameManager::RightPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x + SlopeSize.x + SlopeSize.x / 2  +GameManager::LAYRE_SIZE.x / 2, 
									(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y - SlopeSize.y / 2 - GameManager::LAYRE_SIZE.y / 2));
								//vector�̍ŏ��̏����i�[����
								IteratorLeft = GameManager::LeftPos.begin();
								IteratorRight = GameManager::RightPos.begin();
								//�C�e���[�^�ɂǂ������邩������
								IteratorRight+=SlopeCnt;
								IteratorLeft+=SlopeCnt;
								//�C�e���[�^���i�[����
								GameManager::SaveLeft = *IteratorLeft;
								GameManager::SaveRight = *IteratorRight;
								//�Ζʂ̃X�v���C�g�̍��W��ݒ肷��
								s_slope->setPosition(Vec2(GameManager::SaveLeft.x + SlopeSize.x / 2, GameManager::SaveLeft.y - SlopeSize.y / 2));
							}

							//�ΖʃJ�E���g���C���N�������g
							SlopeCnt++;
							this->addChild(s_slope);

							//���̃��[�v�Ń������m�ۂ������Ȃ�
							flag = false;
						}
				}
			}
		}
	}



	return true;
}


