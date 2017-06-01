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
	CryFloorCnt = 0;
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
						crayfloor.push_back(Sprite::create("Images/CryFloor.png"));

						Vector<Sprite*>::iterator Iterator;
						Iterator = crayfloor.begin();
						Iterator += CryFloorCnt;
						//�A���J�[�|�C���g�ɐݒ肷��
						(*Iterator)->setAnchorPoint(Vec2(0.0f,0.0f));
						//���W��ݒ肷��
						(*Iterator)->
							setPosition(j * GameManager::LAYRE_SIZE.x + /*(GameManager::LAYRE_SIZE.x*2)*/ + GameManager::MapLoopCnt * GameManager::MAP_SIZE.x,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y - (GameManager::LAYRE_SIZE.y * 4));
						//�S�y���Ƀ^�O������
						(*Iterator)->setTag(CryFloorCnt);
						this->addChild((*Iterator));
						//�S�y�����C���N�������g
						CryFloorCnt++;
						//���W��ݒ肷��
						CrayStagePos.push_back(Vec2(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt *  GameManager::MAP_SIZE.x,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y));
						//�T�C�Y���i�[����
						CrayStageSize.push_back(GameManager::MAX_CRAYSTAGESIZE);
					}
				}
			}
		}
	}
	GameManager::AllCrayFloorPos.push_back(CrayStagePos);
	return true;
}


