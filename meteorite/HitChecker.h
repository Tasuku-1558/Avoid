#pragma once
#include "ObjectBase.h"

class Meteorite;
class Player;


class HitChecker final
{
public:
	HitChecker();
	~HitChecker();
	static void PlayerAndMeteorite(Player* player, Meteorite* meteorite[]);		//当たりチェック

	static double GetDirection() { return Direction; }

	static int GetScore() { return Score; }
	static bool GetHit() { return Hit; }
private:
	HitChecker(const HitChecker&);			//コピーコンストラクタ

	static double Direction;

	static int Score;

	static bool Hit;

	//静的定数
	static const float RADIUS_GOOD;
	static const float RADIUS_GREAT;
	static const float RADIUS_EXCELLENT;
	static const float RADIUS_DEAD;

	
};