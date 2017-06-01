/***************************************************************************
*|
*|	�T�v�@�@�j�N���X���`����
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/6/1
*|___________________________________________________________________________
****************************************************************************/
/* ----  �C���N���[�h ---------- */
#include "Needle.h"
/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;


/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@����
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool Needle::init() {

	if (!Node::init()) {

		return false;
	}

	m_needle_cnt = 0;
	//���C���[�擾
	TMXLayer* layer = GameManager::map[GameManager::MapLoopCnt]->getLayer("MapLayer");

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
					std::string str = properties["needle"].asString();
					if (str == "needle")
					{
						//���W��ݒ肷��
						s_needle.push_back(Sprite::create("Images/needle.png"));
						//m_iterator_needle = s_needle.begin();
						s_needle[m_needle_cnt]->setPosition(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt *  GameManager::MAP_SIZE.x + GameManager::LAYRE_SIZE.x / 2,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y - GameManager::LAYRE_SIZE.y / 2);
						this->addChild(s_needle[m_needle_cnt]);
						//�j�̏�Ԃ�^�ɂ���
						m_needle_state.push_back(true);
					
						//���ڂ��J�E���g
						m_needle_cnt++;
					}
				}
			}
		}
	}
	return true;
}