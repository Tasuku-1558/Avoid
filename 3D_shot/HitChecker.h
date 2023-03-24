#pragma once

#include "Math3D.h"
#include "EffectManager.h"
#include <vector>

class Meteorite;
class Player;
class Evaluation;
class ScoreEarn;

using namespace std;

/// <summary>
/// ヒットチェッカークラス
/// </summary>
class HitChecker final
{
public:
	HitChecker(EffectManager* const inEffect);
	virtual ~HitChecker();

	void PlayerAndMeteorite(Player* player, vector<Meteorite*>* meteorite, 
							Evaluation* evaluation, ScoreEarn* scoreEarn);		//プレイヤーとエネミーの衝突判定

	const bool Hit() { return hit; }

private:
	HitChecker(const HitChecker&);			//コピーコンストラクタ

	void MissDecision(Evaluation* evaluation, Player* player);	//miss判定
	void ExcellentDecision(Evaluation* evaluation);				//excellent判定
	void GreatDecision(Evaluation* evaluation);					//great判定
	void GoodDecision(Evaluation* evaluation);					//good判定
	

	EffectManager* effectManager;			//エフェクトマネージャーのポインタ

	bool hit;								//隕石と衝突したか
	bool excellent;							//excellentだったら
	bool miss;								//missだったら
	bool great;								//greatだったら
	bool good;								//goodだったら
	bool decisionFlag;						//判定したか

	//定数
	const float RADIUS_EXCELLENT;		//excellentの範囲
	const float RADIUS_GREAT;			//greatの範囲
	const float RADIUS_GOOD;			//goodの範囲
	const float RADIUS_MISS;			//missの範囲
	const int   SCORE_DECISION_LINE;	//スコア判定ライン
	const int   DECISION_END_LINE;		//判定終了ライン
};