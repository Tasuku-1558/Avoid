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
	void PlayerAndMeteorite(Player* player, Meteorite* meteorite[], MeteoriteManager* meteoriteManager, LargeExplosion* largeexplosion);		//������`�F�b�N
	void Draw();

	double GetDirection() { return direction; }	//�f�o�b�N�p

	int GetScore() { return score; }

	bool GetHit() { return hit; }

private:
	HitChecker(const HitChecker&);			//�R�s�[�R���X�g���N�^

	double direction;

	int score;
	bool hit;
	int excellentGraph;
	bool excellentF;

	float count=0.0f;

	//�ÓI�萔
	static const float RADIUS_GOOD;			//good�͈̔�
	static const float RADIUS_GREAT;		//great�͈̔�
	static const float RADIUS_EXCELLENT;	//excellent�͈̔�
	static const float RADIUS_MISS;			//miss�͈̔�

	static const int   SCORE_GOOD;			//good�̃X�R�A
	static const int   SCORE_GREAT;			//great�̃X�R�A
	static const int   SCORE_EXCELLENT;		//excellent�̃X�R�A
	static const int   SCORE_MISS;			//miss�̃X�R�A

	static const int   FIRST_SCORE;			//�X�R�A�̏����l
	static const int   FIRST_DIRECTION;		//�����̏����l

};