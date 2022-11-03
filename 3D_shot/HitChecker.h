#pragma once

#include <vector>

class MeteoriteManager;
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

	void PlayerAndMeteorite(Player* player, /*Meteorite* meteorite[]*/Meteorite* meteorite, MeteoriteManager* meteoriteManager, Explosion* explosion, Evaluation* evaluation, EarnScore* earnscore);		//������`�F�b�N
	
	double GetDirection() { return direction; }	//�f�o�b�N�p

	bool GetHit() { return hit; }

private:
	HitChecker(const HitChecker&);			//�R�s�[�R���X�g���N�^

	double direction;						//�v���C���[��覐΂̋���

	bool hit;								//覐΂ƏՓ˂�����
	

	//�ÓI�萔
	static const float RADIUS_GOOD;			//good�͈̔�
	static const float RADIUS_GREAT;		//great�͈̔�
	static const float RADIUS_EXCELLENT;	//excellent�͈̔�
	static const float RADIUS_MISS;			//miss�͈̔�
};