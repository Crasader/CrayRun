#pragma once

class GameManager
{
public:
	GameManager();
	~GameManager();
	///////////////UIレイヤー///////////////
	static int ScoreMaxDigit;//最大桁数
	static int TimeMaxDigit;//最大桁数
	static int Digit;//桁数
	static int SaveScore;//スコアを保存する
	static int SpriteCnt;//何個目のスプライトかカウントする
	static bool UsedFlag;//この関数がすでに呼ばれたか
private:

};

