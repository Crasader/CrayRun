/***************************************************************************
*|
*|	�T�v�@�R�C���N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "Coin.h"


USING_NS_CC;

bool Coin::init()
{
	if (!Node::init()) {

		return false;
	}

	//���C���[�擾
	TMXLayer* layer2 = GameManager::map->getLayer("CoinLayer");

	bool flag = true;

	//����:���C���[�̐��𒲂ׂ�,2���:���W��ݒ肷��
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y; i++)
		{
			for (int j = 0; j < GameManager::MAP_SIZE.x / GameManager::LAYRE_SIZE.x; j++)
			{
				//�^�C���̔ԍ�
				unsigned int gid = layer2->getTileGIDAt(Vec2(j, i));

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
						{

							//�摜�������_���Őݒ肷��
							switch (rand() % 3 + 1)
							{
							case 1:
								s_Coin = Sprite::create("Images/coin1.png");
								break;
							case 2:
								s_Coin = Sprite::create("Images/Coin2.png");
							case 3:
								s_Coin = Sprite::create("Images/Coin3.png");
								break;
							default:
								break;
							}
							//���W��ݒ肷��
							s_Coin->
								setPosition(j * GameManager::LAYRE_SIZE.x,
								(GameManager::MAP_SIZE.y / GameManager::LAYRE_SIZE.y - i) * GameManager::LAYRE_SIZE.y);

							s_Coin->setTag(GameManager::CoinCnt);

							this->addChild(s_Coin);

							//���J�E���g���C���N�������g
							GameManager::CoinCnt++;

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


