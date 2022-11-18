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

	void PlayerAndMeteorite(Player* player, Meteorite* meteorite[], Explosion* explosion, Evaluation* evaluation, EarnScore* earnscore);		//������`�F�b�N
	
private:
	HitChecker(const HitChecker&);			//�R�s�[�R���X�g���N�^

	void MissDecision(Evaluation* evaluation, Player* player);	//miss����
	void ExcellentDecision(Evaluation* evaluation);				//excellent����
	void GreatDecision(Evaluation* evaluation);					//great����
	void GoodDecision(Evaluation* evaluation);					//good����
	

	double direction;						//�v���C���[��覐΂̋���
	bool hit;								//覐΂ƏՓ˂�����
	bool slow;
	bool miss;
	bool great;
	bool good;

	//�ÓI�萔
	static const float RADIUS_GOOD;			//good�͈̔�
	static const float RADIUS_GREAT;		//great�͈̔�
	static const float RADIUS_EXCELLENT;	//excellent�͈̔�
	static const float RADIUS_MISS;			//miss�͈̔�
};