/***************************************************************************
*|
*|	�T�v�@�X�R�A�N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  �C���N���[�h ---------- */
#include "CrayStage.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;

/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@����
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool CrayStage::init()
{
	if (!Node::init()) {
		return false;
	}

	//���C���[�擾
	TMXLayer* layer2 = GameManager::map[GameManager::MapLoopCnt]->getLayer("MapLayer");

	bool flag = true;
	int loop_cnt = 0;
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
					std::string str = properties["crayfloor"].asString();
					if (str == "crayfloor")
					{

						//�S�y�����쐬
						m_crayfloor.push_back( CrayStageSprite::create("Images/CryFloor.png"));
						//�A���J�[�|�C���g�ɐݒ肷��
						m_crayfloor[loop_cnt]->setAnchorPoint(Vec2(0.0f, 0.0f));
						//���W��ݒ肷��
						m_crayfloor[loop_cnt]->
							setPosition(j * GameManager::LAYRE_SIZE.x + /*(GameManager::LAYRE_SIZE.x*2)*/ +GameManager::MapLoopCnt * GameManager::MAP_SIZE.x,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y - (GameManager::LAYRE_SIZE.y * 4));
					

						this->addChild(m_crayfloor[loop_cnt]);

						////�T�C�Y��ݒ肷��
						//m_crayfloor->setScale(m_crayfloor->m_size.x, m_crayfloor->m_size.y);
						loop_cnt++;
					}
				}
			}
		}
	}

	return true;
}


