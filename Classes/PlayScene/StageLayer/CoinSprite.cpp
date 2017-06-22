/***************************************************************************
*|
*|	概要　コインクラスの定義
*|　作成者　GS2 16 中田湧介
*|　作成日　2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  インクルード ---------- */
#include "CoinSprite.h"
#include "audio/include/AudioEngine.h"
/* ---- 名前空間を解放 -------------------- */
USING_NS_CC;

/***************************************************************************
*|	概要　　初期化処理
*|	引数　　画像名、ポイント
*|　戻り値　基底クラスの初期化処理が成功したか
****************************************************************************/
bool CoinSprite::init(std::string filename, int point)
{
	if (!Sprite::initWithFile(filename)) {

		return false;
	}

	//ステージレイヤが動き始めてからのフレーム数を初期化
	FlameCnt = 0;
	//吸収されるする距離
	AbsorptionPos = 0.04;
	//引数で受け取った値をポイントとして初期化する
	m_point = point;
	//毎フレーム呼ぶ
	this->scheduleUpdate();

	return true;
}


/***************************************************************************
*|	概要　　スプライトの作成
*|	引数　	画像名、ポイント
*|　戻り値　シーンのアドレス
****************************************************************************/
CoinSprite* CoinSprite::create(std::string filename,int point)
{
	//メモリ確保
	CoinSprite *pRet = new(std::nothrow)CoinSprite();

	if (pRet && pRet->init(filename,point))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}

}


////__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
////	概　要：魔法使いのコイン吸収するかの判定
////	引　数：無し
////　　戻り値：無し
////__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
void CoinSprite::CollisionAbsorptionCoin()
{
	
	Vec2 a = this->getContentSize();
	//プレイヤーとコインの当たり判定
	if (GameManager::HitJudgment
	(this->getPosition(), this->getContentSize(),
	GameManager::PlayerPos - Vec2(0, AbsorptionSize.y/2)/* + Vec2(0.0f,GameManager::PlayerSize.y / 2)-Vec2(AbsorptionSize.x / 2 ,-AbsorptionSize.y / 2)*/, AbsorptionSize) == true)
	{
		//吸収するものtosutu
		m_absorption_flag = true;
	}


}




//魔法使いに吸収するコインを線形補間で動かす
void CoinSprite::AbsorptionCoin()
{
	float TimeStep;
	if (m_Move_Flag == false)
	{
		//移動情報を更新する
		//その時のフレームを保存する
		FlameTime = FlameCnt;
		//スタート時の座標を取得する
		m_startpos = this->getPosition();
		//進む座標を保存する
		m_endpos = GameManager::PlayerPos;

		//2点間の距離を取得する
		SEdis = m_startpos.distance(m_endpos);
		//移動を開始する
		m_Move_Flag = true;
	}

	//移動のフラグ立っている場合
	if (m_Move_Flag == true)
	{
		//目的地に向かって線形補間の処理をする
		//線形補間処理がどのくらい遊んでいるかを割合で求める
		TimeStep = (FlameCnt - FlameTime) / ((SEdis / AbsorptionPos) + 1);

		this->setPosition(Leap(m_startpos, m_endpos, TimeStep));

		//速度を加速させる
		AbsorptionPos += AbsorptionPos;
	}
	//線形補間は途中で終了して移動フラグを降ろす
	if (TimeStep > 0.6f)
	{
		//移動終了したのでフラグを降ろす
		m_Move_Flag = false;
		return;
	}

	//ステージレイヤが動き始めてからのフレーム数を計測
	FlameCnt++;

}

void CoinSprite::update(float data)
{
	////魔法使いなら
	if (GameManager::Mold == GameManager::Witch)
	{
		CollisionAbsorptionCoin();

		//吸収されるフラグが立っているなら
		if (m_absorption_flag == true)
		{
			//魔法使いに吸収するコインを線形補間で動かす
			AbsorptionCoin();
		}
	}

	//コインのあたり判定
	CollisionResponseCoin();
}




/***************************************************************************
*|	概要　　コインあたり判定
*|	引数　　無し
*|　戻り値　無し
****************************************************************************/
void CoinSprite::CollisionResponseCoin()
{

	//プレイヤーとコインの当たり判定
	if (GameManager::HitJudgment
	(this->getPosition(), this->getContentSize(),
		GameManager::PlayerPos, GameManager::PlayerSize) == true)
	{
		//コインの音がtrueの時は回す
		//if (coin_Audio_flag == true)
		//{
		//	//コイン音再生
			experimental::AudioEngine::play2d("Sounds/coin03.ogg");
		//	coin_Audio_flag = false;
		//	coin_cnt = 0;
		//}

		//スコアにとったコインのポイントをたす
		GameManager::Score += m_point;
		//自身を削除
		this->removeFromParent();
	
	}
		
}




	




