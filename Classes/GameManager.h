#pragma once
#include "cocos2d.h"

//方向
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
	//衝突判定(ブロック)
	static int  CollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	//当たり判定
	static bool HitJudgment(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	//衝突判定(斜辺)
	static int DiagonalCollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Bpos, cocos2d::Vec2 Object);
	GameManager();
	~GameManager();
	//////////////キャラクターレイヤー//////
	/////////////キャラクター/////////////
	static cocos2d::Vec2 PlayerSpd;//速度
	static cocos2d::Vec2 PlayerPos;//座標
	static  cocos2d::Vec2 PlayerSize;//サイズ
	static float ScoreCorrection;//スコア補正
	static bool GroundFlag;//地面についているか

	///////////////ステージレイヤー/////////
	//const static int MAX_SLOPE = 50;
	////斜面座標
	//static struct SlopePos
	//{
	//	Vec2 LeftEnd[MAX_SLOPE];//左端
	//	Vec2 RightEnd[MAX_SLOPE];//右端
	//};
	static float SlopePosY;//斜面座標Y
	static bool SlopeFalg;
	///////////////UIレイヤー///////////////
	const static int SCORE_MAX_NUMBER;//スコアのスプライトの数
	const static int DISTANCE_MAX_NUMBER;//スコアのスプライトの数
	static int ScoreMaxDigit;//最大桁数
	static int DistanceMaxDigit;//最大桁数
	static int Digit;//桁数
	static int SaveScore;//スコアを保存する
	static int SaveDistance;//距離を保存する
	static int SpriteCnt;//何個目のスプライトかカウントする
	static bool UsedFlag;//この関数がすでに呼ばれたか

private:

};

