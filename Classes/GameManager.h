/***************************************************************************
*|
*|	�T�v�@�@�Q�[���}�l�[�W���N���X��錾����
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/6/5
*|___________________________________________________________________________
****************************************************************************/
#pragma once
#include "cocos2d.h"



class GameManager 
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

	//�L�����N�^�[
	enum CharacterKind
	{
		Normal,
		Rabbit,
		Gnome,
		Phoenix,
		Slime,
		Witch,

		MaxCharacterKind
	};

	enum Number
	{
		First,
		Second,
		Third,
		Fourth
	};
	////////////////�v���C�V�[��/////////////
	//�Փ˔���(�u���b�N)
	static Direction  CollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	//�Փ˔���2(�u���b�N)
	static	Direction  CollisionDetermination2(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);

	//�Փ˔���(�Ζ�)
	static	Direction DiagonalCollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Bpos, cocos2d::Vec2 Object);
	//�����蔻��
	static	bool HitJudgment(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	static	bool HitJudgment2(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);

	static const cocos2d::Vec2 TOUCH_SIZE;	//�^�b�`�̑傫��

	static	const int BOX_COLLIDER = 10;			//�����蔻�莞�Ɏg�p����^�C�����C���[�̕����班�����������ɓ����Ă��邩�m���߂邽�߂̐�
	static	const int BOX_COLLIDER2 = 40;			//�����蔻�莞�Ɏg�p����^�C�����C���[�̕����班�����������ɓ����Ă��邩�m���߂邽�߂̐�
	
	
	static float WorldPosX;//��ʍ��W
	static bool GameOverFlag;//�Q�[���I�[�o�[�t���O
									
	static bool InvincibleFlag;//���G��Ԃ��ǂ���
	static const cocos2d::Vec2 SCREEN_SIZE;//��ʃT�C�Y


	//////////////�L�����N�^�[���C���[//////
	/////////////�L�����N�^�[/////////////
	static cocos2d::Vec2 PlayerSpd;//���x
	static cocos2d::Vec2 PlayerPos;//���W
	static  cocos2d::Vec2 PlayerSize;//�T�C�Y
	static int JumpCnt;//�W�����v�����
	static bool JumpFlag;//�W�����v�ł��邩
	static bool JumpState;//�W�����v�̖��߂��ꂽ��

	static float ScoreCorrection;//�X�R�A�␳
	static bool RightFlag;//�E���ɓ���������

	static int FirstTouchCnt;//�ŏ��̃^�b�`����ǂꂾ���o�߂�����
	static bool FirstTouchFlag;//�ŏ��̃^�b�`���Ă΂ꂽ��
	
	static int PlayerMapPos;//���Ԗڂ̍��W�ɂ��邩
	///////////////�X�e�[�W���C���[/////////
	//static cocos2d::TMXTiledMap*  map;//�}�b�v
	static std::vector<cocos2d::TMXTiledMap*> map;//�}�b�v

	static const cocos2d::Vec2 MAP_SIZE;//�}�b�v�傫��
	static const cocos2d::Vec2 LAYRE_SIZE;//���C���[�̑傫��
	static int MapLoopCnt;//�X�e�[�W�����[�v��������
	//////////////��///////////////////////
	static std::vector < std::vector< cocos2d::Vec2 >> AllFloorPos;//�����W




	
	
	static float SlopePosY;//�Ζʍ��WY
	/////////////���^/////////////////
	static CharacterKind Mold;//�ǂ̋��^�Ō^������Ă��邩
					//0�F����
					//1�F�e�^
	static bool ChangeMold;//���^��������Ă��邩�ǂ���,true�F�ω�����,false�F�ω��Ȃ�
	static int MoldCnt;//���^�J�E���g
	static std::vector<cocos2d::Vec2> MoldPos;//���^�̍��W
	///////////////UI���C���[///////////////
	///////////////�X�R�A///////////////////
	static int Score;//�X�R�A
	//////////////����//////////////////
	const static int DISTANCE_MAX_NUMBER;//�X�R�A�̃X�v���C�g�̐�
	static int SaveDistance;//������ۑ�����
	static int TotalDistance;//�ŏI�X�R�A

	///////////////////�J����/////////////////////////
	static float m_cameraposx;
	const static float m_cameraspdx;

	//�V�[���ύX���̏�����
	static void Initialize();

	

};



