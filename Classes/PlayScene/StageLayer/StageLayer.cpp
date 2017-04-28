/***************************************************************************
*|
*|	�T�v�@�@���U���g���C���[
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "StageLayer.h"
#include "../CharacterLayer/CharacterLayer.h"]
#include "Manager.h"

USING_NS_CC;

bool StageLayer::init()
{
	if (!Layer::init()) {

		return false;

	}

	/////////�}�b�v�`��////////

	//�^�C���}�b�v�̓ǂݍ���
	//�}�b�v�`�b�v
	GameManager::map = TMXTiledMap::create("floor.tmx");
	//�^�C���}�b�v�̒��S���W��ݒ�
	GameManager::map->setAnchorPoint(Vec2(0, 0));
	//�^�C���}�b�v�̍��W�ݒ�
	GameManager::map->setPosition(Point(0, 0));
	//�摜�̕`��
	this->addChild(GameManager::map);



	//���C���[�Ƀm�[�h���W��
	CrayStage* craystage = CrayStage::create();
	this->addChild(craystage);


	//���C���[�Ƀm�[�h���W��
	Stage* stage = Stage::create();
	this->addChild(stage);

	//���C���[�Ƀm�[�h���W��
	coin = Coin::create();
	this->addChild(coin);
	//���C���[�Ƀm�[�h���W��
	Slope* slope = Slope::create();
	this->addChild(slope);

	this->scheduleUpdate();


	return true;

}


/***************************************************************************
*|	�T�v�@�@���t���[���Ă΂��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void StageLayer::update(float data) {
	AfterHittingCoin();


}

/***************************************************************************
*|	�T�v�@�@�R�C�������蔻���
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void StageLayer::AfterHittingCoin()
{
	

	for (int i = 0; i < GameManager::CoinCnt; i++)
	{
		Node* q = coin->getChildByTag(i);
		if (q != nullptr)
		{
			//�v���C���[�̃R�C��
			if (GameManager::HitJudgment
			(q->getPosition(), q->getContentSize(),
				GameManager::PlayerPos, GameManager::PlayerSize) == true)
			{
				//���������R�C�����폜
				coin->getChildByTag(i)->removeFromParent();
				//�X�R�A�ɂƂ����R�C���̃|�C���g������
				GameManager::Score += GameManager::CoinPoint[i];
			}
		}
	}
};