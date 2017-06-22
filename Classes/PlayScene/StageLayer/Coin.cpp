/***************************************************************************
*|
*|	�T�v�@�R�C���N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  �C���N���[�h ---------- */
#include "Coin.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;

/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@����
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool Coin::init()
{
	if (!Node::init()) {

		return false;
	}


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
					std::string str = properties["coin"].asString();
					if (str == "coin")
					{
						//�摜�������_���Őݒ肷��
						switch (rand() % 3 + 1)
						{
						case 1:
							s_Coin = CoinSprite::create("Images/coin1.png",10);
							break;
						case 2:
							s_Coin = CoinSprite::create("Images/Coin2.png",20);
						case 3:
							s_Coin = CoinSprite::create("Images/Coin3.png",30);
							break;
							break;
						}
						//���W��ݒ肷��
						s_Coin->
							setPosition(j * GameManager::LAYRE_SIZE.x + GameManager::MapLoopCnt * GameManager::MAP_SIZE.x + GameManager::LAYRE_SIZE.x / 2,
							(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y - GameManager::LAYRE_SIZE.y / 2);
						this->addChild(s_Coin ,-100);
					

					}
				}
			}
		}
		
	}
	return true;
}


