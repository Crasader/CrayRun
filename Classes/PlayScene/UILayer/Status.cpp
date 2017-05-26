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

	s_status[Rabbit] = Sprite::create("Images/Rabbit_status.png");
	s_status[Gnome] = Sprite::create("Images/Gnome_status.png");
	s_status[Phoenix] = Sprite::create("Images/Phoenix_status.png");
	s_status[Slime] = Sprite::create("Images/Slime_status.png");


	for (int i = 1; i < 5; i++)
	{
		s_status[i]->setScale(1.2f);
		s_status[i]->setPosition(Vec2(GameManager::PlayerPos.x - 96.0f, 200.0f));
		s_status[i]->setVisible(false);
		this->addChild(s_status[i]);
	}
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
	for (int i = 1; i < 5; i++)
	{
		s_status[i]->setPositionY(GameManager::PlayerPos.y
		+ GameManager::PlayerSize.y / 2);
	}
}
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//�T�v�F�X�v���C�g�̐���
//�����F�Ȃ�
//�߂�l�F�Ȃ�
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
void Status::StatusAction()
{
	Show* action1 = Show::create();
	DelayTime* action2 = DelayTime::create(5.0f);
	Hide* action3 = Hide::create();
	Sequence* action4 = Sequence::create(action1,action2,action3,nullptr);

	switch (GameManager::Mold)
	{
	case Normal:
		break;
	case Rabbit:
		s_status[Rabbit]->runAction(action4);
		break;
	case Gnome:
		s_status[Gnome]->runAction(action4);
		break;
	case Phoenix:
		s_status[Phoenix]->runAction(action4);
		break;
	case Slime:
		s_status[Slime]->runAction(action4);
		break;
	}
}