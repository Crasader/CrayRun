/***************************************************************************
*|
*|	�T�v�@�@�X�e�[�W���C���[
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "StageLayer.h"
#include "../../GameManager.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
//using namespace std;
bool StageLayer::init()
{
	if (!Layer::init()) {

		return false;

	}
	/////////�}�b�v�`��////////

	//�^�C���}�b�v�̓ǂݍ���
	//�}�b�v�`�b�v
	GameManager::map.push_back(TMXTiledMap::create("map1.tmx"));
	IteratorMap = GameManager::map.begin();
	TMXTiledMap* g_Map = *IteratorMap;
	//�^�C���}�b�v�̒��S���W��ݒ�
	g_Map->setAnchorPoint(Vec2(0, 0));
	//�^�C���}�b�v�̍��W�ݒ�
	g_Map->setPosition(Point(0, 0));
	//�摜�̕`��
	this->addChild(g_Map);
	//���C���[�Ƀm�[�h���W��
	craystage.push_back(CrayStage::create());
	ItratorCrayStage=craystage.begin();
	this->addChild((*ItratorCrayStage));
	//���C���[�Ƀm�[�h���W��
	stage = Stage::create();
	this->addChild(stage);
	//���C���[�Ƀm�[�h���W��
	coin.push_back(Coin::create());
	IteratorCoin = coin.begin();
	this->addChild(*IteratorCoin);
	//���C���[�Ƀm�[�h���W��
	slope.push_back(Slope::create());
	IteratorSlope = slope.begin();
	this->addChild(*IteratorSlope);
	//���C���[�Ƀm�[�h���W��
	mold.push_back(Mold::create());
	this->addChild(mold[GameManager::MapLoopCnt]);
	//���C���[�Ƀm�[�h���W��
	needle.push_back(Needle::create());
	ItratorNeedle = needle.begin();
	this->addChild((*ItratorNeedle));
	//�G����
	enemy.push_back(Enemy::create());
	this->addChild(enemy[0]);
	//this->addChild(*(needle.begin()));
	//this->addChild(needle[GameManager::MapLoopCnt]);
	// Register Touch Event
	EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(StageLayer::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(StageLayer::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(StageLayer::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(StageLayer::onTouchesCancelled, this);

	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//_touchListener = listener;

	m_data = 0;


	//�f�o�b�N
	String* b = String::createWithFormat("%i", a);
	n = Label::createWithSystemFont(b->getCString(), "arial", 60);
	n->setScale(4.0f);
	n->setPosition(300, 200);
	this->addChild(n);



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
	n->setString(StringUtils::toString(b));
	n->setPosition(GameManager::PlayerPos);

	Vector<Vec2>::iterator Iterator;
	int i = 0;
	////���̐��������[�v
	//for (Iterator = GameManager::MoldPos.begin(); Iterator != GameManager::MoldPos.end(); ++Iterator)
	//{
	//	Node* q = mold->getChildByTag(i);
	//	Vec2 vec = *Iterator;
	//	vec += GameManager::MoldSpd;
	//	q->setPosition(vec);
	//	i++;
	//}

	//�S�y���̃T�C�Y�ύX
	Vector<Vec2>::iterator g_sizeitertor;
	for (g_sizeitertor = craystage[GameManager::PlayerMapPos]->CrayStageSize.begin(); g_sizeitertor != craystage[GameManager::PlayerMapPos]->CrayStageSize.end();++g_sizeitertor)
	{
		ItratorCrayStage = craystage.begin();
		ItratorCrayStage += GameManager::PlayerMapPos;
		Vector<Sprite*>::iterator SpriteIterator;
		SpriteIterator = (*ItratorCrayStage)->crayfloor.begin();
		SpriteIterator += GameManager::CraySizeChangeCnt;
		(*SpriteIterator)->setScale((*g_sizeitertor).x / GameManager::MAX_CRAYSTAGESIZE.x  , (*g_sizeitertor).y / GameManager::MAX_CRAYSTAGESIZE.y);

	}

	//�R�C�������蔻��
	CollisionResponseCoin();
	//���^�����蔻��
	HittingMold();
	//�j�����蔻��
	HittingNeedle();
	//�G�ƃv���C���̓����蔻��
	HittingEnemy();

	if (static_cast<int>(GameManager::m_cameraposx + 480 ) % static_cast<int>(GameManager::MAP_SIZE.x) == 0)
	{
		//�}�b�v����
		MapCreate();
		if (GameManager::MapLoopCnt > 2)
		{
			//�}�b�v�폜
			MapDelete();
		}

	}

	
		GameManager::CrayFloorSize = craystage[GameManager::PlayerMapPos]->CrayStageSize;
	
}

/***************************************************************************
*|	�T�v�@  �X�e�[�W����
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void StageLayer::MapCreate()
{
	GameManager::MapLoopCnt++;
	//�^�C���}�b�v�̓ǂݍ���
	//�}�b�v�`�b�v
	GameManager::map.push_back(TMXTiledMap::create("floor.tmx"));
	IteratorMap = GameManager::map.begin();
	IteratorMap += GameManager::MapLoopCnt;
//	TMXTiledMap* g_Map = *IteratorMap;
	//�^�C���}�b�v�̒��S���W��ݒ�
	(*IteratorMap)->setAnchorPoint(Vec2(0, 0));
	//�^�C���}�b�v�̍��W�ݒ�
	(*IteratorMap)->setPosition(Point(GameManager::m_cameraposx + 480, 0));
	//�摜�̕`��
	this->addChild((*IteratorMap));
	//�S�y��
	craystage.push_back(CrayStage::create());
	//�C�e���[�^�ɔS�y���̍ŏ��̗v�f���i�[����
	ItratorCrayStage = craystage.begin();
	//���[�v�������}�b�v�̐�������
	ItratorCrayStage+= GameManager::MapLoopCnt;
	this->addChild((*ItratorCrayStage));

	//�X�e�[�W���W���擾
	stage->init();

	//vector�ɃR�C���I�u�W�F�N�g�̃A�h���X���i�[����
	coin.push_back(Coin::create());
	//�C�e���[�^�ɃR�C���̍ŏ��̗v�f���i�[����
	IteratorCoin = coin.begin();
	//���[�v�������}�b�v�̐�������
	IteratorCoin += GameManager::MapLoopCnt;
	this->addChild(*IteratorCoin);



	//�Ζʍ��W���擾
	slope.push_back(Slope::create());
	IteratorSlope = slope.begin();
	IteratorSlope += GameManager::MapLoopCnt;
	this->addChild(*IteratorSlope);


	//���^�쐬
	mold.push_back(Mold::create());
	this->addChild(mold[GameManager::MapLoopCnt]);

	//�j
	needle.push_back(Needle::create());
	this->addChild(needle[GameManager::MapLoopCnt]);

	//�G
	enemy.push_back(Enemy::create());
	this->addChild(enemy[GameManager::MapLoopCnt]);
}
/***************************************************************************
*|	�T�v  �@�X�e�[�W�폜�@
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void StageLayer::MapDelete()
{
	//�}�b�v�̍폜
	IteratorMap = GameManager::map.begin();
	IteratorMap += GameManager::MapLoopCnt - 2;
	(*IteratorMap)->removeFromParent();
	//�X�e�[�W�̍폜
	GameManager::AllFloorPos[GameManager::MapLoopCnt - 2].crend();
	//�Ζʃm�[�h�̍폜
	IteratorSlope -= 2;
	Slope* g_slope = *IteratorSlope;
	g_slope->removeFromParent();

	////�S�y���̍폜
	//ItratorCrayStage -= 2;
	//CrayStage* g_craystage = *ItratorCrayStage;
	//g_craystage->removeFromParent();
	//craystage[GameManager::MapLoopCnt - 2]->removeFromParent();
	//�S�y�����W�̍폜
	GameManager::AllCrayFloorPos[GameManager::MapLoopCnt - 2].crend();

	//�Ζʍ��W�̍폜
	GameManager::AllLeftPos[GameManager::MapLoopCnt - 2].crend();
	GameManager::AllRightPos[GameManager::MapLoopCnt - 2].crend();
	//�R�C���폜

	//���^�폜
	mold[GameManager::MapLoopCnt - 2]->removeFromParent();
	//coin[GameManager::MapLoopCnt - 2]->removeFromParent();

	//�j�폜
	needle[GameManager::MapLoopCnt - 2]->removeFromParent();

	//�G�폜
	enemy[GameManager::MapLoopCnt - 2]->removeFromParent();
}



/***************************************************************************
*|	�T�v�@�@�R�C�������蔻��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void StageLayer::CollisionResponseCoin()
{
	//�R�C�����C���[�̐��������[�v
	//for (IteratorCoin = coin.begin(); IteratorCoin < coin.end(); ++IteratorCoin)
	//{
	int g_LoopCnt = 0;
	IteratorCoin = coin.begin();
	IteratorCoin += GameManager::PlayerMapPos;
		////�R�C���̃f�[�^���ꎞ�I�ɕۑ�����
		Coin* m_SaveCoin = *IteratorCoin;
		for (int i = 0; i < m_SaveCoin->m_CoinCnt; i++)
		{
			//���[�v�������Ԗڂ̃R�C�����擾
			Node* n_coin  = m_SaveCoin->getChildByTag(g_LoopCnt);
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


////__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
////	�T�@�v�F���^�����蔻��
////	���@���F����
////�@�߂�l�F����
////__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
void StageLayer::HittingMold()
{


	if (mold[GameManager::MapLoopCnt]->s_Mold != nullptr)
	{
		//���^�ƃv���C���[���������Ă��邩
		if (GameManager::HitJudgment
		(mold[GameManager::MapLoopCnt]->s_Mold->getPosition(), mold[GameManager::MapLoopCnt]->SIZE,
			GameManager::PlayerPos, GameManager::PlayerSize) == true)
		{
			//�����������^���폜
			//mold[GameManager::MapLoopCnt]->removeFromParent();
			//�e�^�̃L�����N�^�[�ɕύX
			GameManager::Mold = mold[GameManager::MapLoopCnt]->m_kind;
			GameManager::ChangeMold = true;

 		}
	}
}

/***************************************************************************
*|	�T�v�@  �j�ƃv���C���̓����蔻��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void StageLayer::HittingNeedle()
{
	GameManager::GameOverFlag = false;
	//�C�e���[�^�[
	Vector<Sprite*>::iterator IteratorNeedle;
	//���[�v������
	int loop_cnt = 0;
	//
	for (IteratorNeedle = needle[GameManager::PlayerMapPos]->s_needle.begin();
		IteratorNeedle != needle[GameManager::PlayerMapPos]->s_needle.end(); ++IteratorNeedle)
	{
		//�j���Ƃ����Ă��邩
		if (needle[GameManager::PlayerMapPos]->m_needle_state[loop_cnt] == true)
		{
			if (GameManager::HitJudgment(needle[GameManager::PlayerMapPos]->s_needle[loop_cnt]->getPosition() + Vec2(-GameManager::LAYRE_SIZE.x/ 2 , GameManager::LAYRE_SIZE.y / 2),
				GameManager::LAYRE_SIZE, GameManager::PlayerPos, GameManager::PlayerSize) == true)
			{
			//	�Q�[���I�[�o�[�ɂ���
				GameManager::GameOverFlag = true;
			}
		}
		loop_cnt++;
	}


}



/***************************************************************************
*|	�T�v�@�^�b�`���������Ƃ�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void StageLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesMoved");



	//�^�b�`ID�i�[
	int g_touch_id;


	//�^�b�`�̐��������[�v
	for (auto &item : touches)
	{
		//�^�b�`��ID���擾����
		auto touch = item;
		//�^�b�`ID�擾
		g_touch_id = touch->getID();

		//3�ڈȏ�̃^�b�`�͎󂯕t���Ȃ�
		if (g_touch_id < 2)
		{
			//���W���擾����
			touchpos[g_touch_id] = touch->getLocation();
			touchpos[g_touch_id].x += GameManager::m_cameraposx - 480;
		}
	}


	//���ȏ�^�b�`���ꂽ��
	if (g_touch_id >= 1)
	{
		//�S�y���̃}���`�^�b�`����
		MultiTouchCrayStage();
		//�j�̃}���`�^�b�`����
		MultiTouchNeedle();
		//����������
		touchpos[0] = Vec2(0.0f, 0.0f);
		touchpos[1] = Vec2(0.0f, 0.0f);
	}


}

/***************************************************************************
*|	�T�v�@	�S�y���̃}���`�^�b�`����
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void StageLayer::MultiTouchCrayStage()
{
	//�^�b�`��������������
	Direction m_touch_collision_direction[EFFECTIVENESSTOUCH];
	//�^�b�`���L�����N�^�[�ɓ���������
	bool m_touch_collision[EFFECTIVENESSTOUCH];

	Vector<Vec2>::iterator Iterator;

	int g_loop_cnt = 0;
	for (Iterator = GameManager::AllCrayFloorPos[GameManager::PlayerMapPos].begin(); Iterator != GameManager::AllCrayFloorPos[GameManager::PlayerMapPos].end(); ++Iterator)
	{
		Vec2 g_craystage_size = craystage[GameManager::PlayerMapPos]->CrayStageSize[g_loop_cnt];

		//�^�b�`���v���C���[�ɓ���������
		m_touch_collision[0] = GameManager::HitJudgment(
			touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			(*Iterator) + Vec2(g_craystage_size.x / 2, -g_craystage_size.y), g_craystage_size);
		//�^�b�`2���v���C���[�ɓ���������
		m_touch_collision[1] = GameManager::HitJudgment(
			touchpos[1] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			(*Iterator) + Vec2(g_craystage_size.x / 2, -g_craystage_size.y), g_craystage_size);

		//�^�b�`����Ƃ��v���C���[�ɓ���������
		if (m_touch_collision[0] == true && m_touch_collision[1] == true)
		{
			//�^�b�`�ƃv���C���[�̂����蔻��
			m_touch_collision_direction[0] = GameManager::CollisionDetermination2(
				touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
				(*Iterator) + Vec2(g_craystage_size.x / 2, -g_craystage_size.y), g_craystage_size);

			//�^�b�`2�ƃv���C���[�̂����蔻��
			m_touch_collision_direction[1] = GameManager::CollisionDetermination2(
				touchpos[1] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
				(*Iterator) + Vec2(g_craystage_size.x / 2, -g_craystage_size.y), g_craystage_size);



			//��ɋ��񂾂�
			if (m_touch_collision_direction[0] == up || m_touch_collision_direction[1] == under || m_touch_collision_direction[0] == under || m_touch_collision_direction[1] == up)
			{
				/*		int g_distanceY;
				if (touchpos[0].y - touchpos[1].y < 0)
				{
				g_distanceY = touchpos[1].y - touchpos[0].y;
				}
				else {
				g_distanceY = touchpos[0].y - touchpos[1].y;
				}*/

				//�傫���ύX
				craystage[GameManager::PlayerMapPos]->CrayStageSize[g_loop_cnt].y = 32;
				GameManager::CrayFloorSize = craystage[GameManager::PlayerMapPos]->CrayStageSize;
			}
			//���ɋ��񂾂�
			else if (m_touch_collision_direction[0] == left || m_touch_collision_direction[1] == left || m_touch_collision_direction[0] == right || m_touch_collision_direction[1] == right)
			{
				//int g_distanceX;
				//if (touchpos[0].x - touchpos[1].x < 0)
				//{
				//	g_distanceX = touchpos[1].x - touchpos[0].x;
				//}
				//else
				//{
				//	g_distanceX = touchpos[0].x - touchpos[1].x;
				//}
				//�傫���ύX
				craystage[GameManager::PlayerMapPos]->CrayStageSize[g_loop_cnt].x = 32;
				GameManager::CrayFloorSize = craystage[GameManager::PlayerMapPos]->CrayStageSize;
			}
		}

		g_loop_cnt++;
	}
}

/***************************************************************************
*|	�T�v�@  �j�̃}���`�^�b�`����
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void StageLayer::MultiTouchNeedle()
{
	//�^�b�`��������������
	Direction m_touch_collision_direction[EFFECTIVENESSTOUCH];
	//�^�b�`���L�����N�^�[�ɓ���������
	bool m_touch_collision[EFFECTIVENESSTOUCH];

	Vector<Sprite*>::iterator Iterator;
	b = 1;
	int loop_cnt = 0;
	for (Iterator = needle[GameManager::PlayerMapPos]->s_needle.begin(); Iterator != needle[GameManager::PlayerMapPos]->s_needle.end(); ++Iterator)
	{
		b = 2;
		//Vec2 g_craystage_size = craystage[GameManager::PlayerMapPos]->CrayStageSize[loop_cnt];

		//�^�b�`���v���C���[�ɓ���������
		m_touch_collision[0] = GameManager::HitJudgment(
			touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), GameManager::PlayerSize,
			(*Iterator)->getPosition() + Vec2(GameManager::LAYRE_SIZE.x / 2, -GameManager::LAYRE_SIZE.y / 2), GameManager::LAYRE_SIZE);
		//�^�b�`2���v���C���[�ɓ���������
		m_touch_collision[1] = GameManager::HitJudgment(
			touchpos[1] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), GameManager::PlayerSize,
			(*Iterator)->getPosition() + Vec2(GameManager::LAYRE_SIZE.x / 2, -GameManager::LAYRE_SIZE.y /2), GameManager::LAYRE_SIZE);

		//�^�b�`����Ƃ��v���C���[�ɓ���������
		if (m_touch_collision[0] == true && m_touch_collision[1] == true)
		{
			
			//�^�b�`�ƃv���C���[�̂����蔻��
			m_touch_collision_direction[0] = GameManager::CollisionDetermination2(
				touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
				(*Iterator)->getPosition() + Vec2(GameManager::LAYRE_SIZE.x / 2, -GameManager::LAYRE_SIZE.y), GameManager::LAYRE_SIZE);

			//�^�b�`2�ƃv���C���[�̂����蔻��
			m_touch_collision_direction[1] = GameManager::CollisionDetermination2(
				touchpos[1] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
				(*Iterator)->getPosition() + Vec2(GameManager::LAYRE_SIZE.x / 2, -GameManager::LAYRE_SIZE.y), GameManager::LAYRE_SIZE);
			b = (*Iterator)->getPosition().x;


			////���񂾂�
			//if (m_touch_collision_direction[0] == up || m_touch_collision_direction[1] == under || m_touch_collision_direction[0] == under || m_touch_collision_direction[1] == up
			//	||m_touch_collision_direction[0] == left || m_touch_collision_direction[1] == left || m_touch_collision_direction[0] == right || m_touch_collision_direction[1] == right)
			//{
				b = 11111111;
				// ���ʂ̉摜����ύX
				Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/needle2.png");
				(*Iterator)->setTexture(texture);
				needle[GameManager::PlayerMapPos]->m_needle_state[loop_cnt] = false;
		//	}

		}

		loop_cnt++;
	}

}

/***************************************************************************
*|	�T�v�@  �G�ƃv���C���̓����蔻��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void StageLayer::HittingEnemy()
{
	std::vector<Vec2>::iterator IteratorEnemy;
	for (IteratorEnemy = enemy[GameManager::PlayerMapPos]->m_EnemyPos.begin(); IteratorEnemy != enemy[GameManager::PlayerMapPos]->m_EnemyPos.end(); ++IteratorEnemy)
	{
		switch (GameManager::CollisionDetermination
		((*IteratorEnemy), GameManager::LAYRE_SIZE,
			GameManager::PlayerPos, GameManager::PlayerSize))
		{
		case right:
			GameManager::PlayerPos.x = (*IteratorEnemy).x + GameManager::LAYRE_SIZE.x + GameManager::PlayerSize.x / 2 + 1;
			GameManager::PlayerSpd.x = 0.0f;
			GameManager::GameOverFlag = true;
			break;
		case left:
			/*GameManager::PlayerPos.x = GameManager::AllFloorPosx[i] - GameManager::PlayerSize.x / 2;*/
			GameManager::RightFlag = true;
			//GameManager::PlayerSpd.x = -6.0f;
			GameManager::GameOverFlag = true;
			break;
		case up:
			GameManager::PlayerPos.y = (*IteratorEnemy).y;
			GameManager::PlayerSpd.y =0.0f;
			//�W�����v�\�ɂ���
		/*	character->GameManager::JumpCnt = 0;
			character->GameManager::JumpFlag = true;*/
			break;
			case under:
			//GameManager::PlayerPos.y = (*IteratorEnemy).y - ;
			GameManager::PlayerSpd.y = 0.0f;
			GameManager::GameOverFlag = true;
			break;
		default:
			break;

		}

	}
}
