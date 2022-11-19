#pragma once

class Meteorite;
class Player;
class Explosion;
class Evaluation;
class EarnScore;

using namespace std;

class HitChecker final
{
public:
	 HitChecker();
	~HitChecker();

	void PlayerAndMeteorite(Player* player, Meteorite* meteorite[], Explosion* explosion, Evaluation* evaluation, EarnScore* earnscore);		//当たりチェック
	
private:
	HitChecker(const HitChecker&);			//コピーコンストラクタ

	void MissDecision(Evaluation* evaluation, Player* player);	//miss判定
	void ExcellentDecision(Evaluation* evaluation);				//excellent判定
	void GreatDecision(Evaluation* evaluation);					//great判定
	void GoodDecision(Evaluation* evaluation);					//good判定
	

	double direction;						//プレイヤーと隕石の距離
	bool hit;								//隕石と衝突したか
	bool slow;								//動きを遅くするかどうか
	bool miss;
	bool great;
	bool good;
	bool a;

	//静的定数
	static const float RADIUS_GOOD;			//goodの範囲
	static const float RADIUS_GREAT;		//greatの範囲
	static const float RADIUS_EXCELLENT;	//excellentの範囲
	static const float RADIUS_MISS;			//missの範囲
	static const int   SCORE_DECISION_LINE;	//スコア判定ライン
	static const int   DECISION_END_LINE;	//判定終了ライン
};