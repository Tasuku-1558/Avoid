#pragma once

class Meteorite;
class Player;
class Explosion;
class Evaluation;
class ScoreEarn;

using namespace std;

class HitChecker final
{
public:
	 HitChecker();
	~HitChecker();

	void PlayerAndMeteorite(Player* player, Meteorite* meteorite, Explosion* explosion, Evaluation* evaluation, ScoreEarn* scoreearn);		//当たりチェック
	bool Hit() { return hit; }

private:
	HitChecker(const HitChecker&);			//コピーコンストラクタ

	void MissDecision(Evaluation* evaluation, Player* player);	//miss判定
	void ExcellentDecision(Evaluation* evaluation);				//excellent判定
	void GreatDecision(Evaluation* evaluation);					//great判定
	void GoodDecision(Evaluation* evaluation);					//good判定
	

	double direction;						//プレイヤーと隕石の距離
	bool hit;								//隕石と衝突したか
	bool excellent;							//excellentだったら
	bool miss;								//missだったら
	bool great;								//greatだったら
	bool good;								//goodだったら
	bool decisionFlag;						//判定したか

	//静的定数
	static const float RADIUS_GOOD;			//goodの範囲
	static const float RADIUS_GREAT;		//greatの範囲
	static const float RADIUS_EXCELLENT;	//excellentの範囲
	static const float RADIUS_MISS;			//missの範囲
	static const int   SCORE_DECISION_LINE;	//スコア判定ライン
	static const int   DECISION_END_LINE;	//判定終了ライン
};