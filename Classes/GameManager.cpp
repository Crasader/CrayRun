#include "GameManager.h"

int GameManager::ScoreMaxDigit = 0;//最大桁数
int GameManager::TimeMaxDigit = 0;//最大桁数
int GameManager::Digit = 0;//桁数
int GameManager::SaveScore = 0;//スコアを保存する
int GameManager::SpriteCnt = 0;//何個目のスプライトかカウントする
bool GameManager::UsedFlag = false;//この関数がすでに呼ばれたか

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}