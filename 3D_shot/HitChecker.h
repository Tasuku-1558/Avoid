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

	void PlayerAndMeteorite(Player* player, Meteorite* meteorite[]);		//������`�F�b�N

	double GetDirection() { return Direction; }	//�f�o�b�N�p

	int GetScore() { return Score; }
	
private:
	HitChecker(const HitChecker&);			//�R�s�[�R���X�g���N�^

	double Direction;				//�f�o�b�N�p

	int Score;
	

	double dis[10];
	int meteoriteHitChecker[10];

	//�ÓI�萔
	static const float RADIUS_GOOD;			//good�͈̔�
	static const float RADIUS_GREAT;		//great�͈̔�
	static const float RADIUS_EXCELLENT;	//excellent�͈̔�
	static const float RADIUS_MISS;			//miss�͈̔�

};