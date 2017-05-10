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
	stage = Stage::create();
	this->addChild(stage);

	//���C���[�Ƀm�[�h���W��
	coin.push_back(Coin::create());
	IteratorCoin = coin.begin();
	this->addChild(*IteratorCoin);

	//���C���[�Ƀm�[�h���W��
	Slope* slope = Slope::create();
	this->addChild(slope);

	////���C���[�Ƀm�[�h���W��
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

	//�R�C�������蔻��
	CollisionResponseCoin();
	HittingMold();
	HittingFloorToMold();

	if (static_cast<int>(GameManager::m_cameraposx + 480 ) % static_cast<int>(GameManager::MAP_SIZE.x) == 0)
	{
		GameManager::StageLoopCnt++;
		//GameManager::AllFloorPos.push_back(GameManager::StageLoopCnt);
		//�^�C���}�b�v�̓ǂݍ���
		//�}�b�v�`�b�v
		GameManager::map = TMXTiledMap::create("floor.tmx");
		//�^�C���}�b�v�̒��S���W��ݒ�
		GameManager::map->setAnchorPoint(Vec2(0, 0));
		//�^�C���}�b�v�̍��W�ݒ�
		GameManager::map->setPosition(Point(GameManager::m_cameraposx + 480, 0));
		//�摜�̕`��
		this->addChild(GameManager::map);

		//�X�e�[�W���W���擾
		stage->init();

		//vector�ɃR�C���I�u�W�F�N�g�̃A�h���X���i�[����
		coin.push_back(Coin::create());
		//�C�e���[�^�ɃR�C���̍ŏ��̗v�f���i�[����
		IteratorCoin = coin.begin();
		//���[�v�������X�e�[�W�̐�������
		IteratorCoin += GameManager::StageLoopCnt;
		this->addChild(*IteratorCoin);


		//�Ζʍ��W���擾
		slope->init();

	}


}

/***************************************************************************
*|	�T�v�@�@�R�C�������蔻��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void StageLayer::CollisionResponseCoin()
{
	//�R�C�����C���[�̐��������[�v
	for (IteratorCoin = coin.begin(); IteratorCoin < coin.end(); ++IteratorCoin)
	{
		int g_LoopCnt = 0;
		//�R�C���̃f�[�^���ꎞ�I�ɕۑ�����
		Coin* m_SaveCoin = *IteratorCoin;
		for (int i = 0; i < m_SaveCoin->m_CoinCnt; i++)
		{
			//���[�v�������Ԗڂ̃R�C�����擾
			Node* n_coin = m_SaveCoin->getChildByTag(g_LoopCnt);
			if (n_coin != nullptr)
			{
				//�v���C���[�ƃR�C���̓����蔻��
				if (GameManager::HitJudgment
				(n_coin->getPosition(), n_coin->getContentSize(),
					GameManager::PlayerPos, GameManager::PlayerSize) == true)
				{
					//���������R�C�����폜
					m_SaveCoin->getChildByTag(g_LoopCnt)->removeFromParent();
					//�X�R�A�ɂƂ����R�C���̃|�C���g������
					GameManager::Score += GameManager::CoinPoint[g_LoopCnt] * GameManager::ScoreCorrection;
				}
			}
			//���[�v�J�E���g���C���N�������g
			g_LoopCnt++;
		}
	}
}


//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//	�T�@�v�F���^�����蔻��
//	���@���F����
//�@�߂�l�F����
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
void StageLayer::HittingMold()
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
void StageLayer::HittingFloorToMold()
{

	std::vector<Vec2>::iterator Iterator;

	//�}�b�v�̐��������[�v
	for (int j = 0; j <= GameManager::StageLoopCnt; j++)
	{
		//���̐��������[�v
		for (Iterator = GameManager::AllFloorPos[j].begin(); Iterator != GameManager::AllFloorPos[j].end(); ++Iterator)
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