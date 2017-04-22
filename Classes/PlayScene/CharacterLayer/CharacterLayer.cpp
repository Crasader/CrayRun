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
*|	�T�v�@	�v���C���[�ƎΖʂ̂����蔻��
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CharacterLayer::AfterHittingSlope()
{
	Vec2 a = Vec2(200, 200);
	Vec2 b = Vec2(600, 264);

	//�Փ˔���i�Ζʁj
	int HitFlag = GameManager::DiagonalCollisionDetermination(a, b, GameManager::PlayerPos);

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
		//���܂������������o��
		GameManager::PlayerPos.y = GameManager::SlopePosY;
	}


}
