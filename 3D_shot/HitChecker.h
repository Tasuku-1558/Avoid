#pragma once
#include "ObjectBase.h"

class MeteoriteManager;
class Meteorite;
class Player;
class LargeExplosion;

class HitChecker final
{
public:
	 HitChecker();
	~HitChecker();
	void Initialize();
	void PlayerAndMeteorite(Player* player, Meteorite* meteorite[], MeteoriteManager* meteoriteManager, LargeExplosion* largeexplosion);		//当たりチェック
	void Draw();

	double GetDirection() { return direction; }	//デバック用

	int GetScore() { return score; }

	bool GetHit() { return hit; }

private:
	HitChecker(const HitChecker&);			//コピーコンストラクタ

	double direction;

	int score;
	bool hit;
	int excellentGraph;
	bool excellentF;

	float count=0.0f;

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
	static const int   FIRST_DIRECTION;		//距離の初期値

};