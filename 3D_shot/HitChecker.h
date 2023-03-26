#pragma once

#include "Math3D.h"
#include "EffectManager.h"
#include "Evaluation.h"
#include <vector>

class Meteorite;
class Player;
class ScoreEarn;

using namespace std;

/// <summary>
/// ヒットチェッカークラス
/// </summary>
class HitChecker final
{
public:
	HitChecker(EffectManager* const inEffect, Evaluation* const inEvaluation);
	virtual ~HitChecker();

	void PlayerAndMeteorite(Player* player, 
							vector<Meteorite*>* meteorite, 
							ScoreEarn* scoreEarn);				//プレイヤーとエネミーの衝突判定

	const bool Hit() { return hit; }	//隕石と衝突したかを返す

private:
	HitChecker(const HitChecker&);		//コピーコンストラクタ

	void Decision(Player* player);		//各評価の判定

	EffectManager* effectManager;		//エフェクトマネージャーのポインタ
	Evaluation* evaluation;				//評価UIクラスのポインタ

	float distance;						//距離
	bool hit;							//隕石と衝突したか
	bool excellent;						//excellentだったら
	bool miss;							//missだったら
	bool great;							//greatだったら
	bool good;							//goodだったら
	bool decisionFlag;					//判定したか

	//定数
	const int   DECISION_START_LINE;	//判定開始ライン
	const int   DECISION_END_LINE;		//判定終了ライン
	const float RADIUS_EXCELLENT;		//excellentの範囲
	const float RADIUS_GREAT;			//greatの範囲
	const float RADIUS_GOOD;			//goodの範囲
	const float RADIUS_MISS;			//missの範囲
};