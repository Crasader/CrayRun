#pragma once

class GameManager
{
public:
	GameManager();
	~GameManager();
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

