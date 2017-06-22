/***************************************************************************
*|
*|	�T�v�@�@�G�N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/5/17
*|___________________________________________________________________________
****************************************************************************/

/* ----  �C���N���[�h ---------- */
#include "Enemy.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;

/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@����
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool Enemy::init()
{
	if (!Node::init()) {

		return false;

	}
	//���C���[�擾
	TMXLayer* layer = GameManager::map[GameManager::MapLoopCnt]->getLayer("EnemyLayer");

	//����:���C���[�̐��𒲂ׂ�,2���:���W��ݒ肷��
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
					std::string str = properties["enemy"].asString();
					if (str == "enemy")
					{
						////���W��ݒ肷��
						//m_EnemyPos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt * GameManager::MAP_SIZE.x,
						//	(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y));
						//�G�𐶐��A�ݒ�
						m_enemy = EnemySprite::create("Images/enemy1.png");
						m_enemy->setScale(2.0 / 3.0f);
						m_enemy->setAnchorPoint(Vec2(0, 1));
						m_enemy->setPosition((Vec2(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt * GameManager::MAP_SIZE.x,
								(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y)));
						this->addChild(m_enemy);
					}
				}
			}
		}
	}
	return true;
}

