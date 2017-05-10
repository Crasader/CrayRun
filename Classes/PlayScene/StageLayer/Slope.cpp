/***************************************************************************
*|
*|	�T�v�@�ΖʃN���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "Slope.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
bool Slope::init()
{
	if (!Node::init()) {

		return false;
	}

	//���C���[�擾
	TMXLayer* layer = GameManager::map[GameManager::MapLoopCnt]->getLayer("SlopeLayer");
	bool flag = true;
	GameManager::SlopeCnt = 0;

		for (int i = 0; i < GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y; i++)
		{
			for (int j = 0; j < GameManager::MAP_SIZE.x / GameManager::LAYRE_SIZE.x; j++)
			{
				//�^�C���̔ԍ�
				unsigned int gid = layer->getTileGIDAt(Vec2(j, i));

				// �w�肵���^�C���ԍ��̃v���p�e�B�̃Z�b�g���擾
				cocos2d::Value value = GameManager::map[GameManager::MapLoopCnt]->getPropertiesForGID(gid);

				if (value.isNull() == false)
				{
					// �z��Ƃ��ĉ���
					cocos2d::ValueMap properties = value.asValueMap();
					if (properties.empty() == false)
					{
						// "type"�v���p�e�B�𕶎���Ƃ��Ď擾
						std::string str = properties["Coin"].asString();
						if (str == "coin")
						{
							ClimbingFlag = true;
							if (ClimbingFlag == true)
							{
								//�摜��ݒ肷��
								s_slope = Sprite::create("Images/Slope.png");
								//�X���[�v�̃T�C�Y���擾����
								SlopeSize = s_slope->getContentSize();
								//���W��ݒ肷��
								m_LeftPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x - SlopeSize.x / 2 + GameManager::LAYRE_SIZE.x / 2 + GameManager::MapLoopCnt * 1920,
									(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y - SlopeSize.y / 2 - GameManager::LAYRE_SIZE.y/2));
								m_RightPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x + SlopeSize.x/2+ GameManager::LAYRE_SIZE.x / 2 + GameManager::MapLoopCnt * 1920,
									(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y + SlopeSize.y / 2 - GameManager::LAYRE_SIZE.y/2));
								//vector�̍ŏ��̏����i�[����
								IteratorLeft = m_LeftPos.begin();
								IteratorRight = m_RightPos.begin();
								//�C�e���[�^�ɂǂ������邩������
								IteratorRight += GameManager::SlopeCnt;
								IteratorLeft += GameManager::SlopeCnt;
								//�C�e���[�^���i�[����
								m_SaveLeft = *IteratorLeft;
								m_SaveRight = *IteratorRight;
								//�Ζʂ̃X�v���C�g�̍��W��ݒ肷��
								s_slope->setPosition(Vec2(m_SaveLeft.x + SlopeSize.x / 2, 
									m_SaveLeft.y + SlopeSize.y/2));
							}
							//else
							//{
							//	//�摜��ݒ肷��
							//	s_slope = Sprite::create("Images/Slope.png");
							//	//�X���[�v�̃T�C�Y���擾����
							//	SlopeSize = s_slope->getContentSize();
							//	//���W��ݒ肷��
							//	m_LeftPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x - SlopeSize.x / 2 + GameManager::LAYRE_SIZE.x / 2,
							//		(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y + SlopeSize.y / 2 - GameManager::LAYRE_SIZE.y / 2));
							//	m_RightPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x + SlopeSize.x + SlopeSize.x / 2  +GameManager::LAYRE_SIZE.x / 2, 
							//		(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y - SlopeSize.y / 2 - GameManager::LAYRE_SIZE.y / 2));
							//	//vector�̍ŏ��̏����i�[����
							//	IteratorLeft = m_LeftPos.begin();
							//	IteratorRight = m_RightPos.begin();
							//	//�C�e���[�^�ɂǂ������邩������
							//	IteratorRight+= GameManager::SlopeCnt;
							//	IteratorLeft+= GameManager::SlopeCnt;
							//	//�C�e���[�^���i�[����
							//	m_SaveLeft = *IteratorLeft;
							//	m_SaveLeft = *IteratorRight;
							//	//�Ζʂ̃X�v���C�g�̍��W��ݒ肷��
							//	s_slope->setPosition(Vec2(m_SaveLeft.x + SlopeSize.x / 2,m_SaveLeft.y - SlopeSize.y / 2));
							//}


							//�ΖʃJ�E���g���C���N�������g
							GameManager::SlopeCnt++;
							this->addChild(s_slope);
							//���̃��[�v�Ń������m�ۂ������Ȃ�
							flag = false;
						}
				}
			}
		}
	}

		//����̃}�b�v��ɂ���S�Ă̎Ζʍ��W���i�[����
		GameManager::AllLeftPos.push_back(m_LeftPos);
		GameManager::AllRightPos.push_back(m_RightPos);

	return true;
}


