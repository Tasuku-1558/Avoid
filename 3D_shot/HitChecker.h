#pragma once

class MeteoriteManager;
class Meteorite;
class Player;
class Explosion;
class Evaluation;
class Score;

using namespace std;

class HitChecker final
{
public:
	 HitChecker();
	~HitChecker();
	
	void Initialize();

	void PlayerAndMeteorite(Player* player, Meteorite* meteorite[]/*vector<Meteorite*> meteorite*/, MeteoriteManager* meteoriteManager, Explosion* explosion, Evaluation* evaluation);		//当たりチェック
	
	double GetDirection() { return direction; }	//デバック用

	int GetScore() { return score; }

	bool GetHit() { return hit; }

private:
	HitChecker(const HitChecker&);			//コピーコンストラクタ

	double direction;						//プレイヤーと隕石の距離

	int score;								//獲得スコア
	bool hit;								//隕石と衝突したか
	
	//静的定数
	static const float RADIUS_GOOD;			//goodの範囲
	static const float RADIUS_GREAT;		//greatの範囲
	static const float RADIUS_EXCELLENT;	//excellentの範囲
	static const float RADIUS_MISS;			//missの範囲

	static const int   SCORE_GOOD;			//goodのスコア
	static const int   SCORE_GREAT;			//greatのスコア
	static const int   SCORE_EXCELLENT;		//excellentのスコア
	static const int   SCORE_MISS;			//missのスコア

	static const int   FIRST_SCORE;			//スコアの初期値
};