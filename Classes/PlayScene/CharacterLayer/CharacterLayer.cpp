/***************************************************************************
*|
*|	�T�v�@�@���U���g���C���[
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "CharacterLayer.h"

USING_NS_CC;

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

	return true;
}

/***************************************************************************
*|	�T�v�@	���t���[���Ăяo��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::update(float date)
{
	//�ړ�����
	character->Move();
	//�d��
	character->Gravity();
	//�v���C���[�Ə��̏Փ˔���
	AfterHittingFloor();
	//�v���C���[�ƎΖʂ̂����蔻��
	AfterHittingSlope();
}


/***************************************************************************
*|	�T�v�@	�^�b�`���ɌĂяo�����
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesBegan");
	character->Jump();

}

/***************************************************************************
*|	�T�v�@	�X���C�v���ɌĂяo�����
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesMoved");
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
*|	�T�v�@	�v���C���[�Ə��̏Փ˔���
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::AfterHittingFloor()
{
	//���̐��������[�v
	for (int i = 0; i < GameManager::FloorCnt; i++)
	{
		switch (GameManager::CollisionDetermination
		(Vec2(GameManager::FloorPosx[i], GameManager::FloorPosy[i]), GameManager::LAYRE_SIZE,
			GameManager::PlayerPos, GameManager::PlayerSize))
		{
		case right:
			GameManager::PlayerPos.x = GameManager::FloorPosx[i] + GameManager::LAYRE_SIZE.x + GameManager::PlayerSize.x / 2 + 1;
			GameManager::PlayerSpd.x = 0.0f;
			break;
		case left:
			GameManager::PlayerPos.x = GameManager::FloorPosx[i] - GameManager::PlayerSize.x / 2;
			GameManager::PlayerSpd.x = 0.0f;
			break;
		case up:
			GameManager::PlayerPos.y = GameManager::FloorPosy[i];
			GameManager::PlayerSpd.y = 0.0f;
			//GameManager::JumpFlag = true;
			break;
		case under:
			GameManager::PlayerPos.y = GameManager::FloorPosy[i] - GameManager::LAYRE_SIZE.y - GameManager::PlayerSize.y - 1;
			GameManager::PlayerSpd.y = 0.0f;
			break;
		case exception:
			break;

		}
	}
	
}

/***************************************************************************
*|	�T�v�@	�v���C���[�ƎΖʂ̏Փ˔���
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::AfterHittingSlope()
{
	Vec2 a = Vec2(300, 400);
	Vec2 b = Vec2(700, 464);

	//�Փ˔���i�Ζʁj
	Direction HitFlag = GameManager::DiagonalCollisionDetermination(a, b, character->s_player->getPosition());

	//��ɏ������
	if(HitFlag == up)
	{
		GameManager::PlayerSpd.y = 0.0f;
		//���܂������������o��
		GameManager::PlayerPos.y = GameManager::SlopePosY;
		////
		//character->stopAllActions();
	}
	//������Ԃ������Ƃ�
	else if (HitFlag == under)
	{
		////�W�����v�A�N�V�������~�߂�
		character->s_player->stopAllActions();
		//���܂������������o��
		GameManager::PlayerPos.y = GameManager::SlopePosY;
	}


}
