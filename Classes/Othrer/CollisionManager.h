#pragma once
#include "CollisionManager.h"
#include "cocos2d.h"


class CollisionManager
{
public:
	//����
	enum Direction
	{
		up,
		under,
		left,
		right,
		exception
	};



	CollisionManager();
	~CollisionManager();
	////////////////�v���C�V�[��/////////////
	//�Փ˔���(�u���b�N)
	Direction  CollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	//�Փ˔���2(�u���b�N)
	Direction  CollisionDetermination2(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);

	//�Փ˔���(�Ζ�)
	Direction DiagonalCollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Bpos, cocos2d::Vec2 Object);
	//�����蔻��
	bool HitJudgment(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	bool HitJudgment2(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);

	//�V�[���ύX���̏�����
	static void Initialize();

	//�Q�[���}�l�[�W���𐶐�����
	static CollisionManager* GetInstance() {
		//�Q�[���}�l�[�W�������݂��Ă��Ȃ���
		if (gamemanager == nullptr)
		{
			return gamemanager = new CollisionManager();
		}
	}


private:
	
	//�Q�[���}�l�[�W���̃A�h���X���i�[����ϐ�
	static CollisionManager* gamemanager;



private:
	const int BOX_COLLIDER = 10;			//�����蔻�莞�Ɏg�p����^�C�����C���[�̕����班�����������ɓ����Ă��邩�m���߂邽�߂̐�
	const int BOX_COLLIDER2 = 40;			//�����蔻�莞�Ɏg�p����^�C�����C���[�̕����班�����������ɓ����Ă��邩�m���߂邽�߂̐�


};

