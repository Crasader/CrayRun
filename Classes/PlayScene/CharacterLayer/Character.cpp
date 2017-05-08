/***************************************************************************
*|
*|	�T�v�@�X�R�A�N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��,GS2 24 �R�{�I��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "Character.h"


USING_NS_CC;
using namespace cocos2d::experimental;



bool Character::init()
{
	if (!Node::init()) {

		return false;
	}

	//std::string filename = "Images/1.png";
	//if (!Sprite::initWithFile(filename))
	//{

	//	return false;
	//}

	if (s_player == nullptr){
		//�v���C���[�쐬
		s_player = Sprite::create("Images/1.png");
		s_player->setPosition(GameManager::PlayerPos);
		s_player->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(s_player);

	}else{
		Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/1.png");

		s_player->setTexture(texture);
		s_player->setContentSize(texture->getContentSize());
	}
		
	return true;
}

//Character * Character::create()
//{
//	Character *pRet = new(std::nothrow) Character();
//	if (pRet && pRet->init())
//	{
//		pRet->autorelease();
//		return pRet;
//	}
//	else
//	{
//		delete pRet;
//		pRet = nullptr;
//		return nullptr;
//	}
//}

/***************************************************************************
*|	�T�v�@�@�ړ�����
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void Character::Move()
{
	//���W�ɑ��x������
	GameManager::PlayerPos += GameManager::PlayerSpd;
	//���W��K�p������
	s_player->setPosition(GameManager::PlayerPos);
}

/***************************************************************************
*|	�T�v�@  �W�����v
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void Character::Jump()
{
	//JumpBy* jumpaction = JumpBy::create(0.5f, Vec2(0,0), 64.0f, 1);
	//s_player->runAction(jumpaction);
	GameManager::JumpCnt++;

	if (GameManager::JumpFlag == true)
	{
		GameManager::PlayerSpd.y = 9.0f;
	}

	if (GameManager::JumpCnt == 2)
	{
		GameManager::JumpCnt = 0;
		GameManager::JumpFlag = false;
	}
}



