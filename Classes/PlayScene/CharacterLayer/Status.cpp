#include "Status.h"
/// <summary>
/// �T�@�v�F�X�e�[�^�X�̒�`
/// �쐬�ҁFGS2 24 �R�{�I��
/// �쐬���F2017/05/18
/// </summary>

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;

bool Status::init()
{
	//�m�[�h�̍쐬�Ɏ��s������false��Ԃ�
	if (!Node::init())
	{
		return false;
	}

	//�X�v���C�g�̐���
	CreateSprite();


	//���t���[���Ăяo��
	this->scheduleUpdate();

	return true;
}

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//�T�v�F�X�V����
//�����F�Ȃ�
//�߂�l�F�Ȃ�
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
void Status::update(float delta)
{
	//�\�����Ă���5�b�o�߂��Ă��Ȃ��Ȃ�
	if (m_cnt < 300)
	{
		Vec2 pos = s_status->getPosition();
		pos.x += GameManager::m_cameraspdx;
		s_status->setPosition(pos);
	}
	else
	{
		RemoveSelf* deleteSprite = RemoveSelf::create();

		this->runAction(deleteSprite);
	}

	m_cnt++;
}
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//�T�v�F�X�v���C�g�̐���
//�����F�Ȃ�
//�߂�l�F�Ȃ�
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
void Status::CreateSprite()
{
	switch (GameManager::Mold)
	{
	case Normal:
		break;
	case Rabbit:
		s_status = Sprite::create("Images/Rabbit_status.png");
		break;
	case Gnome:
		s_status = Sprite::create("Images/Gnome_status.png");
		break;
	case Phoenix:
		s_status = Sprite::create("Images/Phoenix_status.png");
		break;
	case Slime:
		s_status = Sprite::create("Images/Slime_status.png");
		break;
	}
	s_status->setScale(1.2f);
	s_status->setPosition(Vec2(GameManager::PlayerPos.x - 96.0f, 200.0f));
	this->addChild(s_status);
}
