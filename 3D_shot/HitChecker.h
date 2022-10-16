#pragma once
#include "ObjectBase.h"

class Meteorite;
class Player;

enum Check
{
	HIT, EXCELLENT, GREAT, GOOD
};

class HitChecker final
{
public:
	HitChecker();
	~HitChecker();

	void PlayerAndMeteorite(Player* player, Meteorite* meteorite[]);		//当たりチェック

	double GetDirection() { return Direction; }	//デバック用

	int GetScore() { return Score; }
	
private:
	HitChecker(const HitChecker&);			//コピーコンストラクタ

	double Direction;				//デバック用

	int Score;
	

	double dis[10];
	int meteoriteHitChecker[10];

	//静的定数
	static const float RADIUS_GOOD;			//goodの範囲
	static const float RADIUS_GREAT;		//greatの範囲
	static const float RADIUS_EXCELLENT;	//excellentの範囲
	static const float RADIUS_MISS;			//missの範囲

};