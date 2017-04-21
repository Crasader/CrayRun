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
	//�Փ˔���(�u���b�N)
	static int  CollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	//�����蔻��
	static bool HitJudgment(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	//�Փ˔���(�Ε�)
	static int DiagonalCollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Bpos, cocos2d::Vec2 Object);
	GameManager();
	~GameManager();
	//////////////�L�����N�^�[���C���[//////
	/////////////�L�����N�^�[/////////////
	static cocos2d::Vec2 PlayerSpd;//���x
	static cocos2d::Vec2 PlayerPos;//���W
	static  cocos2d::Vec2 PlayerSize;//�T�C�Y
	static float ScoreCorrection;//�X�R�A�␳
	static bool GroundFlag;//�n�ʂɂ��Ă��邩

	///////////////�X�e�[�W���C���[/////////
	//const static int MAX_SLOPE = 50;
	////�Ζʍ��W
	//static struct SlopePos
	//{
	//	Vec2 LeftEnd[MAX_SLOPE];//���[
	//	Vec2 RightEnd[MAX_SLOPE];//�E�[
	//};
	static float SlopePosY;//�Ζʍ��WY
	static bool SlopeFalg;
	///////////////UI���C���[///////////////
	const static int SCORE_MAX_NUMBER;//�X�R�A�̃X�v���C�g�̐�
	const static int DISTANCE_MAX_NUMBER;//�X�R�A�̃X�v���C�g�̐�
	static int ScoreMaxDigit;//�ő包��
	static int DistanceMaxDigit;//�ő包��
	static int Digit;//����
	static int SaveScore;//�X�R�A��ۑ�����
	static int SaveDistance;//������ۑ�����
	static int SpriteCnt;//���ڂ̃X�v���C�g���J�E���g����
	static bool UsedFlag;//���̊֐������łɌĂ΂ꂽ��

private:

};

