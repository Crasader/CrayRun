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

//キャラクター
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
	////////////////プレイシーン/////////////
	//衝突判定(ブロック)
	static Direction  CollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	//衝突判定2(ブロック)
	static Direction  CollisionDetermination2(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);

	//衝突判定(斜面)
	static Direction DiagonalCollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Bpos, cocos2d::Vec2 Object);
	//当たり判定
	static bool HitJudgment(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	
	static const int BOX_COLLIDER;			//あたり判定時に使用するタイルレイヤーの淵から少しだけ内側に入っているか確かめるための数
	static const int BOX_COLLIDER2;			//あたり判定時に使用するタイルレイヤーの淵から少しだけ内側に入っているか確かめるための数

	GameManager();

	~GameManager();
	static float WorldPosX;//画面座標

	//////////////キャラクターレイヤー//////
	/////////////キャラクター/////////////
	static cocos2d::Vec2 PlayerSpd;//速度
	static cocos2d::Vec2 PlayerPos;//座標
	static  cocos2d::Vec2 PlayerSize;//サイズ
	static float ScoreCorrection;//スコア補正
	static bool RightFlag;//右側に当たったか

	static int FirstTouchCnt;//最初のタッチからどれだけ経過したか
	static bool FirstTouchFlag;//最初のタッチが呼ばれたか
	
	static int PlayerMapPos;//何番目の座標にいるか
	///////////////ステージレイヤー/////////
	//static cocos2d::TMXTiledMap*  map;//マップ
	static std::vector<cocos2d::TMXTiledMap*> map;//マップ

	static const cocos2d::Vec2 MAP_SIZE;//マップ大きさ
	static const cocos2d::Vec2 LAYRE_SIZE;//レイヤーの大きさ
	static int MapLoopCnt;//ステージをループさせた回数
	//////////////床///////////////////////
	static std::vector < std::vector< cocos2d::Vec2 >> AllFloorPos;//床座標


	/////////////斜面//////////////
	static int SlopeCnt;//斜面カウント
	static std::vector<std::vector<cocos2d::Vec2>> AllLeftPos;
	static std::vector<std::vector<cocos2d::Vec2>> AllRightPos;


	/////////////粘土ステージ////////
	static std::vector<std::vector<cocos2d::Vec2>> AllCrayFloorPos;//粘土床座標
	static const cocos2d::Vec2 MAX_CRAYSTAGESIZE;//粘土床の最大サイズ
	static std::vector<cocos2d::Vec2>  CrayFloorSize;//粘土床の大きさ
	static int CraySizeChangeCnt;//どの粘土床のサイズを変更するか
	static bool CraySizeChangeFlag;//粘土床のサイズ変更するか
	static float SlopePosY;//斜面座標Y
	//////////////コイン//////////////
	/////////////金型/////////////////
	static int Mold;//どの金型で型を取っているか
					//0：普通
					//1：兎型
	static bool ChangeMold;//金型がかわっているかどうか,true：変化あり,false：変化なし

	static int MoldCnt;//金型のカウント
	static std::vector<cocos2d::Vec2> MoldPos;//金型の座標
	static cocos2d::Vec2 MoldSpd;//金型の速度
	///////////////UIレイヤー///////////////
	///////////////スコア///////////////////
	static int Score;//スコア
	//////////////距離//////////////////
	const static int DISTANCE_MAX_NUMBER;//スコアのスプライトの数
	static int SaveDistance;//距離を保存する
	static std::vector<int> CoinPoint;//コインのポイント
	///////////////////カメラ/////////////////////////
	static float m_cameraposx;
	const static float m_cameraspdx;

private:

};



