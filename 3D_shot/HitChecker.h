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

	void PlayerAndMeteorite(Player* player, Meteorite* meteorite[]/*vector<Meteorite*> meteorite*/, MeteoriteManager* meteoriteManager, Explosion* explosion, Evaluation* evaluation);		//������`�F�b�N
	
	double GetDirection() { return direction; }	//�f�o�b�N�p

	int GetScore() { return score; }

	bool GetHit() { return hit; }

private:
	HitChecker(const HitChecker&);			//�R�s�[�R���X�g���N�^

	double direction;						//�v���C���[��覐΂̋���

	int score;								//�l���X�R�A
	bool hit;								//覐΂ƏՓ˂�����
	
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
};