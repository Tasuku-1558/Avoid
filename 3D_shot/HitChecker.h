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
	
	double GetDirection() { return direction; }	//デバック用
	
private:
	HitChecker(const HitChecker&);			//コピーコンストラクタ

	double direction;						//プレイヤーと隕石の距離

	bool hit;								//隕石と衝突したか
	bool slow;
	int count;

	//静的定数
	static const float RADIUS_GOOD;			//goodの範囲
	static const float RADIUS_GREAT;		//greatの範囲
	static const float RADIUS_EXCELLENT;	//excellentの範囲
	static const float RADIUS_MISS;			//missの範囲
};