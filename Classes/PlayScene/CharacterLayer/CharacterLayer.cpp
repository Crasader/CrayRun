/***************************************************************************
*|
*|	�T�v�@�@�L�����N�^�[���C���[
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "CharacterLayer.h"
#include "Manager.h"
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
	count = 0;

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
	//�v���C���[�Ə��̏Փ˔���
	CollisionResponseFloor();
	//�v���C���[�ƎΖʂ̂����蔻��
	CollisionResponseSlope();
	//�W�����v���邩���ׂ�
	JumpInvestigate();

	n->setString(StringUtils::toString(a));
	n->setPosition(GameManager::PlayerPos);

	count++;
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
		b = 6;
		//�^�b�`�ƃv���C���[�̂����蔻��
		m_touch_collision_direction[0] = GameManager::CollisionDetermination2(
			touchpos[0] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			GameManager::PlayerPos, GameManager::PlayerSize);
		
		//�^�b�`2�ƃv���C���[�̂����蔻��
		m_touch_collision_direction[1] = GameManager::CollisionDetermination2(
			touchpos[1] - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2), TOUCH_SIZE,
			GameManager::PlayerPos, GameManager::PlayerSize);



		//�㉺�Ńv���C���[�����񂾎�
		if (m_touch_collision_direction[0] == up && m_touch_collision_direction[1] == under)
		{
		
			b = 3;
			//GameManager::PlayerSize.y = touchpos[1].y - touchpos[0].y;
			GameManager::PlayerSize.y = 32.0f;
		}
		else if(m_touch_collision_direction[0] == under && m_touch_collision_direction[1] == up)
		{
			
			b = 2;
			//GameManager::PlayerSize.y = touchpos[0].y - touchpos[1].y;
			GameManager::PlayerSize.y = 32.0f;
		}
		//���E�Ńv���C���[�����񂾎�
		if ((m_touch_collision_direction[0] == left && m_touch_collision_direction[1] == right)
			|| (m_touch_collision_direction[0] == right && m_touch_collision_direction[1] == left))
		{
			GameManager::PlayerSize.x = 30;
		}
		else if ((m_touch_collision_direction[1] == left && m_touch_collision_direction[0] == right)
			|| (m_touch_collision_direction[1] == right && m_touch_collision_direction[0] == left))
		{
			GameManager::PlayerSize.x = 30;
		}
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

void CharacterLayer::ChangeMold()
{
		switch (GameManager::Mold)
		{
		case 0:
			character->removeFromParent();
			character = Character::create();
			//�ύX�����̂Ŗ߂�
			GameManager::ChangeMold = false;

			break;

		case 1:
			character->removeFromParent();
			character = Rabbit::create();
			//�ύX�����̂Ŗ߂�
			GameManager::ChangeMold = false;
			break;
		}
		//�ύX�����̂�addChild����
		this->addChild(character);

}



/***************************************************************************
*|	�T�v�@	�v���C���[�Ə��̏Փ˔���
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::CollisionResponseFloor()
{

	std::vector<Vec2>::iterator Iterator;

	//�}�b�v�̐��������[�v
	for (int i = 0; i <= GameManager::StageLoopCnt; i++)
	{
		//���̐��������[�v
		for (Iterator = GameManager::AllFloorPos[i].begin(); Iterator != GameManager::AllFloorPos[i].end(); ++Iterator)
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
				character->JumpCnt = 0;
				character->JumpFlag = true;
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
	
}

/***************************************************************************
*|	�T�v�@	�v���C���[�ƎΖʂ̏Փ˔���
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::CollisionResponseSlope()
{
	for (int i = 0; i <= GameManager::StageLoopCnt; i++)
	{
		if (i > 0)
		{
			int a = 0;
		}
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
				character->JumpFlag = true;

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
