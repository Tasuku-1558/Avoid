#pragma once
#include "ObjectBase.h"

class Meteorite;
class Player;


class HitChecker final
{
public:
	HitChecker();
	~HitChecker();
	static void PlayerAndMeteorite(Player* player, Meteorite* meteorite[]);		//������`�F�b�N

	static double GetDirection() { return Direction; }

	static int GetScore() { return Score; }
	
private:
	HitChecker(const HitChecker&);			//�R�s�[�R���X�g���N�^

	static double Direction;

	static int Score;


	//�ÓI�萔
	static const float RADIUS_GOOD;
	static const float RADIUS_GREAT;
	static const float RADIUS_EXCELLENT;
	static const float RADIUS_DEAD;

	
};