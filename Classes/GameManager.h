#pragma once
#include "cocos2d.h"

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
	Slime
};

class GameManager 
{
public:
	////////////////�v���C�V�[��/////////////
	//�Փ˔���(�u���b�N)
	static Direction  CollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	//�Փ˔���2(�u���b�N)
	static Direction  CollisionDetermination2(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);

	//�Փ˔���(�Ζ�)
	static Direction DiagonalCollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Bpos, cocos2d::Vec2 Object);
	//�����蔻��
	static bool HitJudgment(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	
	static const int BOX_COLLIDER;			//�����蔻�莞�Ɏg�p����^�C�����C���[�̕����班�����������ɓ����Ă��邩�m���߂邽�߂̐�
	static const int BOX_COLLIDER2;			//�����蔻�莞�Ɏg�p����^�C�����C���[�̕����班�����������ɓ����Ă��邩�m���߂邽�߂̐�

	GameManager();

	~GameManager();
	static float WorldPosX;//��ʍ��W

	//////////////�L�����N�^�[���C���[//////
	/////////////�L�����N�^�[/////////////
	static cocos2d::Vec2 PlayerSpd;//���x
	static cocos2d::Vec2 PlayerPos;//���W
	static  cocos2d::Vec2 PlayerSize;//�T�C�Y
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


	/////////////�Ζ�//////////////
	static int SlopeCnt;//�ΖʃJ�E���g
	static std::vector<std::vector<cocos2d::Vec2>> AllLeftPos;
	static std::vector<std::vector<cocos2d::Vec2>> AllRightPos;


	/////////////�S�y�X�e�[�W////////
	static std::vector<std::vector<cocos2d::Vec2>> AllCrayFloorPos;//�S�y�����W
	static const cocos2d::Vec2 MAX_CRAYSTAGESIZE;//�S�y���̍ő�T�C�Y
	static std::vector<cocos2d::Vec2>  CrayFloorSize;//�S�y���̑傫��
	static int CraySizeChangeCnt;//�ǂ̔S�y���̃T�C�Y��ύX���邩
	static bool CraySizeChangeFlag;//�S�y���̃T�C�Y�ύX���邩
	static float SlopePosY;//�Ζʍ��WY
	//////////////�R�C��//////////////
	/////////////���^/////////////////
	static int Mold;//�ǂ̋��^�Ō^������Ă��邩
					//0�F����
					//1�F�e�^
	static bool ChangeMold;//���^��������Ă��邩�ǂ���,true�F�ω�����,false�F�ω��Ȃ�

	static int MoldCnt;//���^�̃J�E���g
	static std::vector<cocos2d::Vec2> MoldPos;//���^�̍��W
	static cocos2d::Vec2 MoldSpd;//���^�̑��x
	///////////////UI���C���[///////////////
	///////////////�X�R�A///////////////////
	static int Score;//�X�R�A
	//////////////����//////////////////
	const static int DISTANCE_MAX_NUMBER;//�X�R�A�̃X�v���C�g�̐�
	static int SaveDistance;//������ۑ�����
	static std::vector<int> CoinPoint;//�R�C���̃|�C���g
	///////////////////�J����/////////////////////////
	static float m_cameraposx;
	const static float m_cameraspdx;

private:

};



