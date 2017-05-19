/***************************************************************************
*|
*|	�T�v�@�@�L�����N�^�[���C���[
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "CharacterLayer.h"

USING_NS_CC;


/* ---- ���O��Ԃ���� -------------------- */
bool CharacterLayer::init()
{
	if (!Layer::init()) {

		return false;

	}
	log("############################### CHARsCTERLAYER created");

	//���C���[�Ƀm�[�h���W��
	character = Character::create();
	this->addChild(character);



	//���t���[���Ăяo��
	this->scheduleUpdate();

	// Register Touch Event
	EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(CharacterLayer::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(CharacterLayer::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(CharacterLayer::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(CharacterLayer::onTouchesCancelled, this);

	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//_touchListener = listener;

	//�f�o�b�N
	String* b = String::createWithFormat("%i", a);
	n = Label::createWithSystemFont(b->getCString(), "arial", 60);
	n->setScale(4.0f);
	n->setPosition(300, 200);
	this->addChild(n);

	int FirstTouchCnt = 0;//�ŏ��̃^�b�`����ǂꂾ���o�߂�����
	//bool FirstTouchFlag = false;//�ŏ��̃^�b�`���Ă΂ꂽ��

	
	
	return true;
}

/***************************************************************************
*|	�T�v�@	���t���[���Ăяo��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::update(float date)
{
	//���^���ύX����Ă���ꍇ
	if (GameManager::ChangeMold == true) {
		//�^��ύX����
		ChangeMold();
	}

	//�ړ�����
	character->Move();
	//�d��
	character->Gravity();
	//���Ԗڂ̃}�b�v�ɂ��邩���߂�
	character->GetLoopPos();


	//�v���C���[�Ə��̏Փ˔���
	CollisionResponseFloor();
	if(GameManager::Mold != Gnome)
	//�v���C���[�ƔS�y���̏Փ˔���
	CollisionResponseCrayFloor();
	//�v���C���[�ƎΖʂ̂����蔻��
	CollisionResponseSlope();
	//�W�����v���邩���ׂ�
	JumpInvestigate();


	n->setString(StringUtils::toString(a));
	n->setPosition(GameManager::PlayerPos);

	//�T�C�Y�ύX
	character->setScale();

	n->setString(StringUtils::toString(b));
	n->setPosition(GameManager::PlayerPos + Vec2(300, 0));

}


/***************************************************************************
*|	�T�v�@	�^�b�`���ɌĂяo�����
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{	


	for (auto &item : touches)
	{
		//�^�b�`�̃A�h���X���i�[����
		auto touch = item;
	
		if (FirstTouchFlag == false)
		{
			
			//�ŏ��̃^�b�`���Ă΂ꂽ��^
			//���̃^�b�`�܂ł̃J�E���g���n�߂�
			FirstTouchFlag = true;
			
		}
		else
		{
			//�ŏ��̃^�b�`�t���O���U�ɂ���
			FirstTouchFlag = false;
			//�ŏ��̃^�b�`�J�E���g������������
			FirstTouchCnt = 0;
		}
	}
	log("onTouchesBegan");
	
}

/***************************************************************************
*|	�T�v�@	�X���C�v���ɌĂяo�����
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesMoved");
	//�^�b�`�̐��������[�v
	for (auto &item : touches)
	{
		//�^�b�`��ID���擾����
		auto touch = item;
		m_touch_id = touch->getID();
	
		//3�ڈȏ�̃^�b�`�͎󂯕t���Ȃ�
		if (m_touch_id < 2)
		{
			//���W���擾����
			touchpos[m_touch_id] = touch->getLocation();
			touchpos[m_touch_id].x += GameManager::m_cameraposx - 480;
		}
	}


	//���ȏ�^�b�`���ꂽ��
	if (m_touch_id >= 1)
	{
		//�L�����N�^�[�̃}���`�^�b�`����
		MultiTouchCharacter();

		//����������
		touchpos[0] = Vec2(0.0f, 0.0f);
		touchpos[1] = Vec2(0.0f, 0.0f);
	}
}

/***************************************************************************
*|	�T�v�@	�������Ƃ�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesEnded");
}

/***************************************************************************
*|	�T�v�@	�L�����Z�����ꂽ�Ƃ�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesCancelled");
}


/***************************************************************************
*|	�T�v�@	�L�����N�^�[�̃}���`�^�b�`����
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::MultiTouchCharacter()
{
	//�^�b�`��������������
	Direction m_touch_collision_direction[EFFECTIVENESS_TOUCH];
	//�^�b�`���L�����N�^�[�ɓ���������
	bool m_touch_collision[EFFECTIVENESS_TOUCH];

	//�^�b�`���v���C���[�ɓ���������
	m_touch_collision[0] = GameManager::HitJudgment(
		touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
		GameManager::PlayerPos, GameManager::PlayerSize);
	//�^�b�`2���v���C���[�ɓ���������
	m_touch_collision[1] = GameManager::HitJudgment(
		touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
		GameManager::PlayerPos, GameManager::PlayerSize);

	//�^�b�`����Ƃ��v���C���[�ɓ���������
	if (m_touch_collision[0] == true && m_touch_collision[1] == true)
	{
		//�^�b�`�ƃv���C���[�̂����蔻��
		m_touch_collision_direction[0] = GameManager::CollisionDetermination2(
			touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			GameManager::PlayerPos, GameManager::PlayerSize);

		//�^�b�`2�ƃv���C���[�̂����蔻��
		m_touch_collision_direction[1] = GameManager::CollisionDetermination2(
			touchpos[1] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			GameManager::PlayerPos, GameManager::PlayerSize);


		//�㉺�ɋ���ł��邩���Ƃ̑傫���̏ꍇ
		if (m_touch_collision_direction[0] == up || m_touch_collision_direction[1] == under || m_touch_collision_direction[0] == under || m_touch_collision_direction[1] == up && character->isScaleY == false)
		{
			//�傫���ύX
			GameManager::PlayerSize.y = 32.0f;
			if(GameManager::Mold != Slime)
			character->isScaleY = true;
		}
		//���E�ɋ���ł��邩���̑傫���̏ꍇ
		else if (m_touch_collision_direction[0] == left || m_touch_collision_direction[1] == left || m_touch_collision_direction[0] == right || m_touch_collision_direction[1] == right && character->isScaleX == false)
		{
			//�傫���ύX
			GameManager::PlayerSize.x = 32;
			if (GameManager::Mold != Slime)
				character->isScaleX = true;
		}
	}
}



//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//
//�T�v�F���^�ɂ��L�����N�^�̕ύX
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

void CharacterLayer::ChangeMold()
{
		switch (GameManager::Mold)
		{
		case Normal:
			character->removeFromParent();
			character = Character::create();
			//�ύX�����̂Ŗ߂�
			GameManager::ChangeMold = false;
			break;
		case Rabbit:
			character->removeFromParent();
			character = Rabbit::create();
			//�ύX�����̂Ŗ߂�
			GameManager::ChangeMold = false;
			break;
		case Gnome:
			//�ύX�����̂Ŗ߂�
			character->removeFromParent();
			character = Gnome::create();
			GameManager::ChangeMold = false;
			break;
		case Phoenix:
			//�ύX�����̂Ŗ߂�
			character->removeFromParent();
			character = Phoenix::create();
			GameManager::ChangeMold = false;
			break;
		case Slime:
			character->removeFromParent();
			character = Slime::create();
			//�ύX�����̂Ŗ߂�
			GameManager::ChangeMold = false;
			break;
		}
		//�ύX�����̂�addChild����
		this->addChild(character);

		status = Status::create();
		addChild(status);
}





/***************************************************************************
*|	�T�v�@	�v���C���[�Ə��̏Փ˔���
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::CollisionResponseFloor()
{

	std::vector<Vec2>::iterator Iterator;

	//////�}�b�v�̐��������[�v
		//���̐��������[�v
		for (Iterator = GameManager::AllFloorPos[GameManager::PlayerMapPos].begin(); Iterator != GameManager::AllFloorPos[GameManager::PlayerMapPos].end(); ++Iterator)
		{
			Vec2 vec = *Iterator;
			switch (GameManager::CollisionDetermination
			(vec, GameManager::LAYRE_SIZE,
				GameManager::PlayerPos, GameManager::PlayerSize))
			{
			case right:
				GameManager::PlayerPos.x = vec.x + GameManager::LAYRE_SIZE.x + GameManager::PlayerSize.x / 2 + 1;
				GameManager::PlayerSpd.x = 0.0f;
				break;
			case left:
				/*GameManager::PlayerPos.x = GameManager::AllFloorPosx[i] - GameManager::PlayerSize.x / 2;*/
				GameManager::RightFlag = true;
				GameManager::PlayerSpd.x = -6.0f;
				break;
			case up:
				GameManager::PlayerPos.y = vec.y;
				GameManager::PlayerSpd.y = 0.0f;
				//�W�����v�\�ɂ���
				GameManager::JumpCnt = 0;
				GameManager::JumpFlag = true;
				break;
				/*case under:
				GameManager::PlayerPos.y = GameManager::AllFloorPosy[i] - GameManager::LAYRE_SIZE.y - GameManager::PlayerSize.y - 1;
				GameManager::PlayerSpd.y = 0.0f;
				break;*/
			default:
				break;

				}
		}	
}

/***************************************************************************
*|	�T�v�@	�v���C���[�ƔS�y���̏Փ˔���
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::CollisionResponseCrayFloor()
{
	std::vector<Vec2>::iterator Iterator;
	std::vector<Vec2>::iterator IteratorSize;
	//���[�v������
	int g_loop_cnt = 0;
	//////�}�b�v�̐��������[�v
//	b = GameManager::CrayFloorSize[g_loop_cnt].y;

	//���̐��������[�v
	for (Iterator = GameManager::AllCrayFloorPos[GameManager::PlayerMapPos].begin(); Iterator != GameManager::AllCrayFloorPos[GameManager::PlayerMapPos].end(); ++Iterator)
	{
		//�C�e���[�^�[�ɍŏ��̗v�f��������
		IteratorSize = GameManager::CrayFloorSize.begin();
		//���ڂ�����΂�����������
		IteratorSize += g_loop_cnt;
		
		if (IteratorSize == GameManager::CrayFloorSize.end())
		{
			GameManager::CrayFloorSize.insert(GameManager::CrayFloorSize.begin() + g_loop_cnt, Vec2(192, 320));
			//GameManager::CrayFloorSize[g_loop_cnt] = Vec2(192, 320);
		}
		//�C�e���[�^�[�ɍŏ��̗v�f��������
		IteratorSize = GameManager::CrayFloorSize.begin();
		//���ڂ�����΂�����������
		IteratorSize += g_loop_cnt;

		Vec2 vec = *Iterator;
		switch (GameManager::CollisionDetermination
		(vec + Vec2( GameManager::MAX_CRAYSTAGESIZE.x / 2 - (*IteratorSize).x / 2, -(GameManager::MAX_CRAYSTAGESIZE.y - (*IteratorSize).y)),(*IteratorSize),
			GameManager::PlayerPos, GameManager::PlayerSize))
		{
		case right:
			GameManager::PlayerPos.x = vec.x + GameManager::MAX_CRAYSTAGESIZE.x  -  (*IteratorSize).x / 2 - GameManager::PlayerSize.x / 2;
			GameManager::PlayerSpd.x = 0.0f;
			b = 1;
			break;
		case left:
			GameManager::PlayerPos.x = vec.x + GameManager::MAX_CRAYSTAGESIZE.x / 2 - (*IteratorSize).x / 2 - GameManager::PlayerSize.x / 2;
			GameManager::RightFlag = true;
			GameManager::PlayerSpd.x = -6.0f;
			b = 2;
			break;
		case up:
			b = (*IteratorSize).y;
			GameManager::PlayerPos.y = vec.y  - GameManager::MAX_CRAYSTAGESIZE.y + (*IteratorSize).y;
			GameManager::PlayerSpd.y = 0.0f;
			//�W�����v�\�ɂ���
			GameManager::JumpCnt = 0;
			GameManager::JumpFlag = true;
		
			break;
			case under:
			//GameManager::PlayerPos.y = GameManager::AllFloorPosy[i] - GameManager::LAYRE_SIZE.y - GameManager::PlayerSize.y - 1;
			//GameManager::PlayerSpd.y = 0.0f;
			break;
		default:
			break;

		}
		//�J�E���g�𑝂₷
		g_loop_cnt++;
	}
}

/***************************************************************************
*|	�T�v�@	�v���C���[�ƎΖʂ̏Փ˔���
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::CollisionResponseSlope()
{
	for (int i = 0; i <= GameManager::MapLoopCnt; i++)
	{

		//�ŏ��̎ΖʉE�[���i�[����
		IteratorLeft = GameManager::AllLeftPos[i].begin();
		//vector�̐��������[�v
		for (IteratorRight = GameManager::AllRightPos[i].begin(); IteratorRight != GameManager::AllRightPos[i].end(); ++IteratorRight)
		{
			//�Փ˔���i�Ζʁj
			Direction HitFlag = GameManager::DiagonalCollisionDetermination(*IteratorLeft, *IteratorRight, GameManager::PlayerPos/*character->s_player->getPosition()*/);
			//��ɏ������
			if (HitFlag == up)
			{
				GameManager::PlayerSpd.y = 0.0f;
				//���܂������������o��
				GameManager::PlayerPos.y = GameManager::SlopePosY;
				//�W�����v�\�ɂ���
				GameManager::JumpCnt = 0;
				GameManager::JumpFlag = true;

			}
			IteratorLeft++;
		}

	}
}

/***************************************************************************
*|	�T�v�@	�W�����v���邩���ׂ�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::JumpInvestigate()
{

	//�ŏ��̃^�b�`�t���O���^�Ȃ�
	if (FirstTouchFlag == true)
	{
		FirstTouchCnt++;
	}
	//���ڂ̃^�b�`����1�b�ȏ�o�߂����Ȃ�

	if (FirstTouchCnt > 4)
	{
		//�W�����v�֐����Ă�
		character->Jump();
		//�ŏ��̃^�b�`�t���O���U�ɂ���
		FirstTouchFlag = false;
		//�ŏ��̃^�b�`�J�E���g������������
		FirstTouchCnt = 0;
	}
}
