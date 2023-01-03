#pragma once

#include "Math3D.h"

class Meteorite;
class Player;
class Explosion;
class Evaluation;
class ScoreEarn;

/// <summary>
/// �q�b�g�`�F�b�J�[�N���X
/// </summary>
class HitChecker final
{
public:
	 HitChecker();
	~HitChecker();

	void PlayerAndMeteorite(Player* player, Meteorite* meteorite, Explosion* explosion, Evaluation* evaluation, ScoreEarn* scoreearn);		//������`�F�b�N
	bool Hit() { return hit; }

private:
	HitChecker(const HitChecker&);			//�R�s�[�R���X�g���N�^

	void MissDecision(Evaluation* evaluation, Player* player);	//miss����
	void ExcellentDecision(Evaluation* evaluation);				//excellent����
	void GreatDecision(Evaluation* evaluation);					//great����
	void GoodDecision(Evaluation* evaluation);					//good����
	

	double direction;						//�v���C���[��覐΂̋���
	bool hit;								//覐΂ƏՓ˂�����
	bool excellent;							//excellent��������
	bool miss;								//miss��������
	bool great;								//great��������
	bool good;								//good��������
	bool decisionFlag;						//���肵����

	//�ÓI�萔
	static const float RADIUS_GOOD;			//good�͈̔�
	static const float RADIUS_GREAT;		//great�͈̔�
	static const float RADIUS_EXCELLENT;	//excellent�͈̔�
	static const float RADIUS_MISS;			//miss�͈̔�
	static const int   SCORE_DECISION_LINE;	//�X�R�A���胉�C��
	static const int   DECISION_END_LINE;	//����I�����C��
};