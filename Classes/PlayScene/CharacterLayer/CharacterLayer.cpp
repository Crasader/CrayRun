/***************************************************************************
*|
*|	�T�v�@�@�L�����N�^�[���C���[�N���X
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  �C���N���[�h ---------- */
#include "CharacterLayer.h"


/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
using namespace experimental;

/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@����
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool CharacterLayer::init()
{
	if (!Layer::init()) {

		return false;

	}

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
	int FirstTouchCnt = 0;//�ŏ��̃^�b�`����ǂꂾ���o�߂�����


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
	//�W�����v���邩���ׂ�
	JumpInvestigate();
	//�T�C�Y�ύX
	character->setScale();
	//�L�����N�^��������
	character->JumpBan();





	//�W�����v�̖��߂��I��������Ƃɂ���
	if (GameManager::PlayerSpd.y < 4)
	{
		GameManager::JumpState = false;
	}




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




	////���ȏ�^�b�`���ꂽ��
	if (m_touch_id >= 1)
	{

	//	if (FirstMultiTouchFlag == false)
	//	{
	//		for (int i = 0; i < EFFECTIVENESS_TOUCH; i++)
	//		{
	//			FirstPos[i] = touchpos[i];
	//			SavePlayerPosx = GameManager::PlayerPos.x;
	//		}
	//		FirstMultiTouchFlag = true;
	//�L�����N�^�[�̃}���`�^�b�`����
		MultiTouchCharacter();
		}


		

	//	//����������
	//	touchpos[0] = Vec2(0.0f, 0.0f);
	//	touchpos[1] = Vec2(0.0f, 0.0f);
	//}
}

/***************************************************************************
*|	�T�v�@	�������Ƃ�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesEnded");

	//for (int i = 0; i < EFFECTIVENESS_TOUCH; i++)
	//{
	//	FirstPos[i] = Vec2(0.0f, 0.0f);
	//}

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
	////�^�b�`��������������
	//Direction m_touch_collision_direction[EFFECTIVENESS_TOUCH];
	//�^�b�`���L�����N�^�[�ɓ���������
	bool m_touch_collision[EFFECTIVENESS_TOUCH];

	//�^�b�`���v���C���[�ɓ���������
	m_touch_collision[0] = GameManager::HitJudgment2(
		touchpos[0] /*- Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2)*/, Vec2(0,0),
	Vec2(GameManager::PlayerPos.x - GameManager::PlayerSize.x/ 2 - GameManager::PlayerSize.x, 
		GameManager::PlayerPos.y), GameManager::PlayerSize);
	
	if (m_touch_collision[0] == true && character->isScale == false)
	{
		GameManager::PlayerSize.x = 16;
		character->isScale = true;
		PlaySandWicheSE();
	}


	//�^�b�`���v���C���[�ɓ���������
	m_touch_collision[0] = GameManager::HitJudgment2(
		touchpos[1]/* - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2)*/, Vec2(0, 0),
		Vec2(GameManager::PlayerPos.x - GameManager::PlayerSize.x / 2 - GameManager::PlayerSize.x,
			GameManager::PlayerPos.y), GameManager::PlayerSize);

	if (m_touch_collision[0] == true && character->isScale == false)
	{
		GameManager::PlayerSize.x = 16;
		character->isScale = true;
		PlaySandWicheSE();
	}


	//�^�b�`���v���C���[�ɓ���������
	m_touch_collision[0] = GameManager::HitJudgment2(
		touchpos[0] /*- Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2)*/, Vec2(0,0),
		Vec2(GameManager::PlayerPos.x + GameManager::PlayerSize.x / 2 ,
			GameManager::PlayerPos.y  ), GameManager::PlayerSize);
	if (m_touch_collision[0] == true && character->isScale == false)
	{
		GameManager::PlayerSize.x = 16;
		character->isScale = true;
		PlaySandWicheSE();
	}



	//�^�b�`2���v���C���[�ɓ���������
	m_touch_collision[1] = GameManager::HitJudgment2(
		touchpos[0] /*- Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2)*/, Vec2(0, 0),
		Vec2(GameManager::PlayerPos.x - GameManager::PlayerSize.x/2,
			GameManager::PlayerPos.y + GameManager::PlayerSize.y ), GameManager::PlayerSize);

	
	if (m_touch_collision[1] == true && character->isScale == false)
	{
		GameManager::PlayerSize.y = 32;
		character->isScale = true;
		PlaySandWicheSE();
	}

	//�^�b�`2���v���C���[�ɓ���������
	m_touch_collision[1] = GameManager::HitJudgment2(
		touchpos[1] /*- Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2)*/, Vec2(0, 0),
		Vec2(GameManager::PlayerPos.x - GameManager::PlayerSize.x / 2,
			GameManager::PlayerPos.y + GameManager::PlayerSize.y), GameManager::PlayerSize);


	if (m_touch_collision[1] == true && character->isScale == false)
	{
		GameManager::PlayerSize.y = 32;
		character->isScale = true;
		PlaySandWicheSE();
	}


	//�^�b�`2���v���C���[�ɓ���������
	m_touch_collision[1] = GameManager::HitJudgment2(
		touchpos[1] /*- Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2)*/, Vec2(0, 0),
		Vec2(GameManager::PlayerPos.x - GameManager::PlayerSize.x / 2,
			GameManager::PlayerPos.y + GameManager::PlayerSize.y), GameManager::PlayerSize);


	if (m_touch_collision[1] == true && character->isScale == false)
	{
		GameManager::PlayerSize.y = 32;
		character->isScale = true;
		PlaySandWicheSE();

	}

	//�^�b�`2���v���C���[�ɓ���������
	m_touch_collision[1] = GameManager::HitJudgment2(
		touchpos[0]/* - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2)*/, Vec2(0, 0),
		Vec2(GameManager::PlayerPos.x + GameManager::PlayerSize.x / 2,
			GameManager::PlayerPos.y - GameManager::PlayerSize.y), GameManager::PlayerSize);

	if (m_touch_collision[1] == true && character->isScale == false)
	{
				character->isScale = true;

		GameManager::PlayerSize.y = 32;
		PlaySandWicheSE();
	}
	//�^�b�`2���v���C���[�ɓ���������
	m_touch_collision[1] = GameManager::HitJudgment2(
		touchpos[1]/* - Vec2(TOUCH_SIZE.x / 2, -TOUCH_SIZE.y / 2)*/, Vec2(0, 0),
		Vec2(GameManager::PlayerPos.x + GameManager::PlayerSize.x / 2,
			GameManager::PlayerPos.y - GameManager::PlayerSize.y), GameManager::PlayerSize);

	if (m_touch_collision[1] == true && character->isScale == false)
	{
		character->isScale = true;

		GameManager::PlayerSize.y = 32;
		PlaySandWicheSE();
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
	//�O��ƈႤ�L�����N�^�^�C�v��
	if (old_chara_kind != GameManager::Mold)
	{
		//���̃{�C�X�ƍ�����Ȃ��悤�ɍĐ����̃{�C�X���~�߂�
		CharacterVoiceStop();

		switch (GameManager::Mold)
		{
		case GameManager::Normal:
			character->removeFromParent();
			character = Character::create();
			//�m�[���{�C�X�Đ�
			m_character_voice[GameManager::Normal] = AudioEngine::play2d("Sounds/domovoice.mp3");
			//�ύX�����̂Ŗ߂�
			GameManager::ChangeMold = false;
			break;
		case GameManager::Rabbit:
			character->removeFromParent();
			character = Rabbit::create();
			//�E�T�M�{�C�X�Đ�
			m_character_voice[GameManager::Rabbit] = AudioEngine::play2d("Sounds/RabbitVoice.mp3");
			break;
		case GameManager::Gnome:
			//�ύX�����̂Ŗ߂�
			character->removeFromParent();
			character = Gnome::create();
			m_character_voice[GameManager::Gnome] = AudioEngine::play2d("Sounds/Gnome_VoiceSE.mp3");
			break;
		case GameManager::Phoenix:
			//�ύX�����̂Ŗ߂�
			character->removeFromParent();
			character = Phoenix::create();
			m_character_voice[GameManager::Phoenix] = AudioEngine::play2d("Sounds/phoenix_CrySE.mp3");
			break;
		case GameManager::Slime:
			character->removeFromParent();
			character = Slime::create();
			m_character_voice[GameManager::Slime] = AudioEngine::play2d("Sounds/SlimeSE.mp3");
			break;
		case GameManager::Witch:
			character->removeFromParent();
			character = Witch::create();
			m_character_voice[GameManager::Witch] = AudioEngine::play2d("Sounds/Witch.mp3");
		}
		//�ύX�����̂�addChild����
		this->addChild(character);
	}
		//�W�����v�������Z�b�g����
		GameManager::JumpCnt = 0;
		GameManager::JumpFlag = true;
		//����̃L�����^�C�v��ۑ�����
		old_chara_kind = GameManager::Mold;
}





/***************************************************************************
*|	�T�v�@	�v���C���[�Ə��̏Փ˔���
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::CollisionResponseFloor()
{
	int hitcnt = 0;
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
			case GameManager::right:
			
				/*GameManager::PlayerPos.x = vec.x + GameManager::LAYRE_SIZE.x + GameManager::PlayerSize.x / 2 + 1;
				GameManager::PlayerSpd.x = 0.0f;
				hitcnt++;*/
				break;

			case GameManager::left:

				//	�Q�[���I�[�o�[�ɂ���
				GameManager::GameOverFlag = true;

				GameManager::PlayerPos.x = vec.x - GameManager::PlayerSize.x / 2;
				//GameManager::RightFlag = true;
				//GameManager::PlayerSpd.x = -6.0f;
				//���������̂Œׂ��
				/*character->s_player->setAnchorPoint(Vec2(0, 0));
				GameManager::PlayerSize.x = 32;
				GameManager::PlayerPos.x += 16;*/


				hitcnt++;
				break;
			case GameManager::up:
				GameManager::PlayerPos.y = vec.y;
				GameManager::PlayerSpd.y = 0.0f;
				//�W�����v�\�ɂ���
				GameManager::JumpCnt = 0;
				GameManager::JumpFlag = true;
				hitcnt++;

			//	character->GroundFlag = true;
				break;
				case GameManager::under:
				GameManager::PlayerPos.y = vec.y - GameManager::LAYRE_SIZE.y - GameManager::PlayerSize.y-10;
				GameManager::PlayerSpd.y = 0.0f;
				hitcnt++;
				break;
			default:
				break;

				}
		}	
		
		//�������������Ă��邩
		if (hitcnt > 2)
		{
			//�傫�������ɖ߂��������s��Ȃ�
			character->FloormultipleFlag = true;
		}
		else
		{
			//�傫�������ɖ߂��������s��
			character->FloormultipleFlag = false;
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

	if (FirstTouchCnt > 6)
	{
		//�W�����v�֐����Ă�
		character->Jump();
		//�ŏ��̃^�b�`�t���O���U�ɂ���
		FirstTouchFlag = false;
		//�ŏ��̃^�b�`�J�E���g������������
		FirstTouchCnt = 0;

		GameManager::JumpState = true;
	}
}

/***************************************************************************
*|	�T�v�@	�L�����N�^�{�C�X��S�Ď~�߂�֐�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::CharacterVoiceStop()
{
	for (int i = 0; i < GameManager::MaxCharacterKind; i++) /*if (m_character_voice[i] != 0)*/AudioEngine::stop(m_character_voice[i]);
}
