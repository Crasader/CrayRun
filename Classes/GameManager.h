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

class GameManager 
{
public:
	////////////////�v���C�V�[��/////////////
	//�Փ˔���(�u���b�N)
	static Direction  CollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	//�Փ˔���(�Ζ�)
	static Direction DiagonalCollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Bpos, cocos2d::Vec2 Object);
	//�����蔻��
	static bool HitJudgment(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	
	static const int BOX_COLLIDER;			//�����蔻�莞�Ɏg�p����^�C�����C���[�̕����班�����������ɓ����Ă��邩�m���߂邽�߂̐�

	GameManager();

	~GameManager();
	//////////////�L�����N�^�[���C���[//////
	/////////////�L�����N�^�[/////////////
	static cocos2d::Vec2 PlayerSpd;//���x
	static cocos2d::Vec2 PlayerPos;//���W
	static  cocos2d::Vec2 PlayerSize;//�T�C�Y
	static float ScoreCorrection;//�X�R�A�␳
	static bool JumpFlag;//�n�ʂɂ��Ă��邩
	static bool RightFlag;//�E���ɓ���������
	static int JumpCnt;//�W�����v�t���O

	static int FirstTouchCnt;//�ŏ��̃^�b�`����ǂꂾ���o�߂�����
	static bool FirstTouchFlag;//�ŏ��̃^�b�`���Ă΂ꂽ��
	
	///////////////�X�e�[�W���C���[/////////
	static cocos2d::TMXTiledMap*  map;//�}�b�v
	static const cocos2d::Vec2 MAP_SIZE;//�}�b�v�傫��
	static const cocos2d::Vec2 LAYRE_SIZE;//���C���[�̑傫��
	
	//////////////��///////////////////////
	static std::vector<cocos2d::Vec2> FloorPos;//�����W
	//const static int MAX_SLOPE = 50;
	////�Ζʍ��W

	static std::vector<cocos2d::Vec2> LeftPos;//���[
	static std::vector<cocos2d::Vec2> RightPos;//�E�[

	//�C�e���[�^�̒l���i�[����
	static cocos2d::Vec2 SaveRight;
	static cocos2d::Vec2 SaveLeft;

	static float SlopePosY;//�Ζʍ��WY
	//////////////�R�C��//////////////

	static int CoinCnt;//�R�C�����J�E���g
	///////////////UI���C���[///////////////
	///////////////�X�R�A///////////////////
	static std::vector<cocos2d::Sprite*> s_score;//�R�C��
	const static int SCORE_MAX_NUMBER;//�X�R�A�̃X�v���C�g�̐�
	static int ScoreMaxDigit;//�ő包��
	static int Score;//�X�R�A
	static int SaveScore;//�X�R�A��ۑ�����

	//////////////����//////////////////
	const static int DISTANCE_MAX_NUMBER;//�X�R�A�̃X�v���C�g�̐�
	static int DistanceMaxDigit;//�ő包��
	static int Digit;//����
	static float Distance;//����
	static int SaveDistance;//������ۑ�����
	static int SpriteCnt;//���ڂ̃X�v���C�g���J�E���g����
	static bool UsedFlag;//���̊֐������łɌĂ΂ꂽ��
	static std::vector<int> CoinPoint;//�R�C���̃|�C���g
	///////////////////�J����/////////////////////////

	static float m_cameraposx;
	const static float m_cameraspdx;

private:

};



