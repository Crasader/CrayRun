/***************************************************************************
*|
*|	�T�v�@�@�X�e�[�W���C���[�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  �C���N���[�h ---------- */
#include "../../GameManager.h"
#include "StageLayer.h"
#include "audio/include/AudioEngine.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;


//using namespace std;
/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@����
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool StageLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	////�}�b�v����
	//MapCreate();
	



	// Register Touch Event
	EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(StageLayer::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(StageLayer::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(StageLayer::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(StageLayer::onTouchesCancelled, this);

	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//_touchListener = listener;

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
	/*n->setString(StringUtils::toString(b));
	n->setPosition(GameManager::PlayerPos);*/

	
	Vector<Vec2>::iterator Iterator;
	int loop_cnt = 0;

	if (static_cast<int>(GameManager::m_cameraposx - 480) % static_cast<int>(GameManager::MAP_SIZE.x) == 0)
	{
			
			//�}�b�v����
			MapCreate();
			//////��
			stage = Stage::create();
			this->addChild(stage);
	
			if (GameManager::MapLoopCnt > 1)
			{
				//�X�e�[�W�폜
				MapDelete();
			}
			GameManager::MapLoopCnt++;
	}
	//���^�����蔻��
	HittingMold();
	////�R�C���̉���true�̎��͉�
	//if (coin_Audio_flag == false)
	//{
	//	coin_cnt++;
	//}
	//if (coin_cnt > 60)
	//{
	//	coin_Audio_flag = true;
	//	coin_cnt = 0;
	//}

	
}

/***************************************************************************
*|	�T�v�@  �X�e�[�W����
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void StageLayer::MapCreate()
{

	//�^�C���}�b�v�̓ǂݍ���
	int NowMap = rand() % MAX_MAP + 1;
	//�O��Ƃ͈Ⴄ�}�b�v�ɂȂ�悤�Ƀ��[�v����
	while (OldMap == NowMap)
	{
		NowMap = rand() % MAX_MAP + 1;
	}


	//�O��̃}�b�v���X�V����
	OldMap = NowMap;
	std::ostringstream MapName;

	//��T�ڂ܂ł͊ȒP�ȃX�e�[�W���쐬����
	if (GameManager::MapLoopCnt == 0)
	{
		MapName << "Map/EasyMap" << NowMap << ".tmx";
		//�}�b�v�`�b�v
		GameManager::map.push_back(TMXTiledMap::create(MapName.str()));
		//GameManager::map.push_back(TMXTiledMap::create("Map/NewMap1.tmx"));
	}
	else
	{
		MapName << "Map/NewMap" << NowMap << ".tmx";
		//�}�b�v�`�b�v
		GameManager::map.push_back(TMXTiledMap::create(MapName.str()));
		//GameManager::map.push_back(TMXTiledMap::create("Map/NewMap2.tmx"));
	}
	
//	TMXTiledMap* g_Map = *IteratorMap;
	//�^�C���}�b�v�̒��S���W��ݒ�
	GameManager::map[GameManager::MapLoopCnt]->setAnchorPoint(Vec2(0, 0));
	//�^�C���}�b�v�̍��W�ݒ�
	GameManager::map[GameManager::MapLoopCnt]->setPosition(Point(GameManager::MAP_SIZE.x * GameManager::MapLoopCnt, 0));
	//�摜�̕`��
	this->addChild(GameManager::map[GameManager::MapLoopCnt]);


	//�S�y��
	craystage.push_back(CrayStage::create());
	this->addChild(craystage[GameManager::MapLoopCnt]);

	

	//�Ζʍ��W���擾
	slope.push_back(Slope::create());
	this->addChild(slope[GameManager::MapLoopCnt]);

	//���^�쐬
	mold.push_back(Mold::create());
	this->addChild(mold[GameManager::MapLoopCnt]);

	//�j
	needle.push_back(Needle::create());
	this->addChild(needle[GameManager::MapLoopCnt]);

	//�G
	enemy.push_back(Enemy::create());
	this->addChild(enemy[GameManager::MapLoopCnt]);

	//�R�C��
	coin.push_back(Coin::create());
	this->addChild(coin[GameManager::MapLoopCnt], -100);
}
/***************************************************************************
*|	�T�v  �@�X�e�[�W�폜�@
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void StageLayer::MapDelete()
{
	//b = DeleteCnt;
	//�}�b�v�̍폜

	GameManager::map[GameManager::MapLoopCnt - 2]->removeFromParent();


	//�X�e�[�W�̍폜
	//std::remove(GameManager::AllFloorPos,DeleteCnt);
	//�Ζʃm�[�h�̍폜
	slope[GameManager::MapLoopCnt- 2]->removeFromParent();

	//�S�y���̍폜
	craystage[GameManager::MapLoopCnt - 2]->removeFromParent();

	//���^�폜
	mold[GameManager::MapLoopCnt - 2]->removeFromParent();
	//coin[GameManager::MapLoopCnt - 2]->removeFromParent();

	//�j�폜
	needle[GameManager::MapLoopCnt - 2]->removeFromParent();

	//�G�폜
	enemy[GameManager::MapLoopCnt - 2]->removeFromParent();
}



////__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
////	�T�@�v�F���^�����蔻��
////	���@���F����
////�@�߂�l�F����
////__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
void StageLayer::HittingMold()
{
	//���^�X�v���C�g�̃C�e���[�^
	std::vector<Sprite*>::iterator IteratorMold;
	//���[�v������
	int loop_cnt = 0;
	for (IteratorMold = mold[GameManager::PlayerMapPos]->s_Mold.begin(); IteratorMold != mold[GameManager::PlayerMapPos]->s_Mold.end(); IteratorMold++)
	{


		if ((*IteratorMold) != nullptr)
		{
			//���^�ƃv���C���[���������Ă��邩
			if (GameManager::HitJudgment
			((*IteratorMold)->getPosition() , mold[GameManager::PlayerMapPos]->SIZE,
				GameManager::PlayerPos + Vec2(GameManager::PlayerSize.x / 2, GameManager::PlayerSize.y / 2), GameManager::PlayerSize) == true)
			{
				//�����������^���폜
				//(*IteratorMold)->removeFromParent();
				
				//�e�^�̃L�����N�^�[�ɕύX
				GameManager::Mold = mold[GameManager::PlayerMapPos]->m_kind[loop_cnt];
				GameManager::ChangeMold = true;
				//���^�A�N�V����
				//�A�N�V�������~�߂�
				//(*IteratorMold)->stopAllActions();
				//mold[GameManager::PlayerMapPos]->s_BackMold[loop_cnt]->stopAllActions();

				//���ރA�N�V����
				MoveBy* action1 = MoveBy::create(0.01f, Vec2(12, 0));
				(*IteratorMold)->runAction(action1);
				(*IteratorMold)->setScale(1.4f, 1.4f);

				MoveBy* action2 = MoveBy::create(0.01f, Vec2(-13.0f, 0.0f));
				CallFunc* action3 = CallFunc::create(CC_CALLBACK_0(StageLayer::MoldParticle, this, (*IteratorMold)->getPosition()- Vec2(70, 0)));
				Sequence* action4 = Sequence::create(action2, action3, nullptr);

				mold[GameManager::PlayerMapPos]->s_BackMold[loop_cnt]->runAction(action4);
				mold[GameManager::PlayerMapPos]->s_BackMold[loop_cnt]->setScale(1.4f, 1.4f);


				//���^�p�[�e�B�N��
				//StageLayer::MoldParticle((*IteratorMold)->getPosition() + Vec2(12, 0));

				(*IteratorMold) = nullptr;

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
	//�L���ȃ^�b�`�̐�
	const int EFFECTIVENESSTOUCH = 2;
	//�^�b�`���W
	cocos2d::Vec2 touchpos[EFFECTIVENESSTOUCH];


	//�^�b�`�̐��������[�v
	for (auto &item : touches)
	{
		//�^�b�`��ID���擾����
		auto touch = item;
		//�^�b�`ID�擾
		g_touch_id = touch->getID();

		//3�ڈȏ�̃^�b�`�͎󂯕t���Ȃ�
		if (g_touch_id < EFFECTIVENESSTOUCH)
		{
			//���W���擾����
			touchpos[g_touch_id] = touch->getLocation();
			touchpos[g_touch_id].x += GameManager::m_cameraposx - 480;
		}
	}


	//���ȏ�^�b�`���ꂽ��
	if (g_touch_id >= 1)
	{
		std::vector<NeedleSprite*>::iterator needle_iterator;
		for (needle_iterator = needle[GameManager::PlayerMapPos]->m_needleSprite.begin();
			needle_iterator !=  needle[GameManager::PlayerMapPos]->m_needleSprite.end();
			needle_iterator++)
		{
			(*needle_iterator)->MultiTouchColliosion(*touchpos);
		}
		

		//����������
		touchpos[0] = Vec2(0.0f, 0.0f);
		touchpos[1] = Vec2(0.0f, 0.0f);
	}


}




//���^�p�[�e�B�N��
void StageLayer::MoldParticle(cocos2d::Vec2 Position)
{

	// �쐬�����p�[�e�B�N���̃v���p�e�B���X�g��ǂݍ���
	ParticleSystemQuad* particle = ParticleSystemQuad::create("Particle/particle_texture2.plist");
	//�p�[�e�B�N���̃������[���[�N����i���d�v�j
	particle->setAutoRemoveOnFinish(true);
	// �p�[�e�B�N�����J�n
	particle->resetSystem();
	// �p�[�e�B�N����\������ꏊ�̐ݒ�
	particle->setPosition(Position);
	//�p�[�e�B�N���̃X�P�[��
	particle->setScale(0.5);
	// �p�[�e�B�N����z�u
	this->addChild(particle);

	////�p�[�e�B�N���̃A�N�V����
	DelayTime* action = DelayTime::create(1.0f);
	RemoveSelf* action2 = RemoveSelf::create();
	Sequence* action3 = Sequence::create(action,action2,nullptr);
	particle->runAction(action3);

	experimental::AudioEngine::play2d("Sounds/mold.mp3");
	
}

