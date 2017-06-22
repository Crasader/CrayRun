/***************************************************************************
*|
*|	概要　　ゲームマネージャクラスを宣言する
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/6/5
*|___________________________________________________________________________
****************************************************************************/
#pragma once
#include "cocos2d.h"



class GameManager 
{
public:
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
	////////////////プレイシーン/////////////
	//衝突判定(ブロック)
	static Direction  CollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	//衝突判定2(ブロック)
	static	Direction  CollisionDetermination2(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);

	//衝突判定(斜面)
	static	Direction DiagonalCollisionDetermination(cocos2d::Vec2 Apos, cocos2d::Vec2 Bpos, cocos2d::Vec2 Object);
	//当たり判定
	static	bool HitJudgment(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);
	static	bool HitJudgment2(cocos2d::Vec2 Apos, cocos2d::Vec2 Asize, cocos2d::Vec2 Bpos, cocos2d::Vec2 Bsize);

	static const cocos2d::Vec2 TOUCH_SIZE;	//タッチの大きさ

	static	const int BOX_COLLIDER = 10;			//あたり判定時に使用するタイルレイヤーの淵から少しだけ内側に入っているか確かめるための数
	static	const int BOX_COLLIDER2 = 40;			//あたり判定時に使用するタイルレイヤーの淵から少しだけ内側に入っているか確かめるための数
	
	
	static float WorldPosX;//画面座標
	static bool GameOverFlag;//ゲームオーバーフラグ
									
	static bool InvincibleFlag;//無敵常態かどうか
	static const cocos2d::Vec2 SCREEN_SIZE;//画面サイズ


	//////////////キャラクターレイヤー//////
	/////////////キャラクター/////////////
	static cocos2d::Vec2 PlayerSpd;//速度
	static cocos2d::Vec2 PlayerPos;//座標
	static  cocos2d::Vec2 PlayerSize;//サイズ
	static int JumpCnt;//ジャンプする回数
	static bool JumpFlag;//ジャンプできるか
	static bool JumpState;//ジャンプの命令されたか

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




	
	
	static float SlopePosY;//斜面座標Y
	/////////////金型/////////////////
	static CharacterKind Mold;//どの金型で型を取っているか
					//0：普通
					//1：兎型
	static bool ChangeMold;//金型がかわっているかどうか,true：変化あり,false：変化なし
	static int MoldCnt;//金型カウント
	static std::vector<cocos2d::Vec2> MoldPos;//金型の座標
	///////////////UIレイヤー///////////////
	///////////////スコア///////////////////
	static int Score;//スコア
	//////////////距離//////////////////
	const static int DISTANCE_MAX_NUMBER;//スコアのスプライトの数
	static int SaveDistance;//距離を保存する
	static int TotalDistance;//最終スコア

	///////////////////カメラ/////////////////////////
	static float m_cameraposx;
	const static float m_cameraspdx;

	//シーン変更時の初期化
	static void Initialize();

	

};



