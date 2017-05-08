/***************************************************************************
*|
*|	�T�v�@�@�X�e�[�W���C���[
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "StageLayer.h"
#include "../CharacterLayer/CharacterLayer.h"
#include "../../GameManager.h"
/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;

bool StageLayer::init()
{
	if (!Layer::init()) {

		return false;

	}
	log("############################### StageLayer created");

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

	//���C���[�Ƀm�[�h���W��
	Rmold = RabbitMold::create();
	this->addChild(Rmold);

	this->scheduleUpdate();

	return true;

}


/***************************************************************************
*|	�T�v�@�@���t���[���Ă΂��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void StageLayer::update(float data) 
{
	Rmold->Gravity();
	Vector<Vec2>::iterator Iterator;

	int i = 0;
	//���̐��������[�v
	for (Iterator = GameManager::MoldPos.begin(); Iterator != GameManager::MoldPos.end(); ++Iterator)
	{
		Node* q = Rmold->getChildByTag(i);
		Vec2 vec = *Iterator;
		vec += GameManager::MoldSpd;
		q->setPosition(vec);

		i++;
	}


	AfterHittingCoin();
	AfterHittingMold();
	AfterHittingFloorToMold();

	if (static_cast<int>(GameManager::m_cameraposx + 480 ) % static_cast<int>(GameManager::MAP_SIZE.x) == 0)
	{
		GameManager::StageLoopCnt++;
		//GameManager::FloorPos.push_back(GameManager::StageLoopCnt);
		//�^�C���}�b�v�̓ǂݍ���
		//�}�b�v�`�b�v
		GameManager::map = TMXTiledMap::create("floor.tmx");
		//�^�C���}�b�v�̒��S���W��ݒ�
		GameManager::map->setAnchorPoint(Vec2(0, 0));
		//�^�C���}�b�v�̍��W�ݒ�
		GameManager::map->setPosition(Point(GameManager::m_cameraposx + 480, 0));
		//�摜�̕`��
		this->addChild(GameManager::map);
		////���C���[�Ƀm�[�h���W��
		Stage* stage = Stage::create();
		this->addChild(stage);
	}


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
				GameManager::Score += GameManager::CoinPoint[i] * GameManager::ScoreCorrection;
			}
		}
	}
};

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//	�T�@�v�F���^�����蔻���
//	���@���F����
//�@�߂�l�F����
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
void StageLayer::AfterHittingMold()
{
	for (int i = 0; i < GameManager::MoldCnt; i++)
	{
		Node* q = Rmold->getChildByTag(i);
		if (q != nullptr)
		{
			//���^
			if (GameManager::HitJudgment
			(q->getPosition(), q->getContentSize(),
				GameManager::PlayerPos, GameManager::PlayerSize) == true)
			{
				//�����������^���폜
				Rmold->getChildByTag(i)->removeFromParent();
				//�e�^�̃L�����N�^�[�ɕύX
				GameManager::Mold = 1;
				GameManager::ChangeMold = true;
			}
		}
	}
};

/***************************************************************************
*|	�T�v�@	���^�Ə��̏Փ˔���
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void StageLayer::AfterHittingFloorToMold()
{

	std::vector<Vec2>::iterator Iterator;

	//�}�b�v�̐��������[�v
	for (int j = 0; j <= GameManager::StageLoopCnt; j++)
	{
		//���̐��������[�v
		for (Iterator = GameManager::FloorPos[j].begin(); Iterator != GameManager::FloorPos[j].end(); ++Iterator)
		{
			for (int i = 0; i < GameManager::MoldCnt; i++)
			{
				Node* q = Rmold->getChildByTag(i);
				if (q != nullptr) {
					Vec2 vec = *Iterator;
					switch (GameManager::CollisionDetermination
					(vec, GameManager::LAYRE_SIZE,
						q->getPosition(), q->getContentSize())
						)
					{
					case up:
						q->setPositionY(vec.y);
						GameManager::MoldSpd.y = 0.0f;
					}
				}
			}
		}
	}
}