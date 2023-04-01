#pragma once

#include <vector>
#include "Math3D.h"
#include "EffectManager.h"
#include "Evaluation.h"

class Meteorite;
class Player;
class ScoreEarn;

using namespace std;

/// <summary>
/// �q�b�g�`�F�b�J�[�N���X
/// </summary>
class HitChecker final
{
public:
	HitChecker(EffectManager* const inEffect, Evaluation* const inEvaluation);
	virtual ~HitChecker();

	void PlayerAndMeteorite(Player* player, 
							vector<Meteorite*>* meteorite, 
							ScoreEarn* scoreEarn);			//�v���C���[�ƃG�l�~�[�̏Փ˔���

	const bool Hit() { return hit; }	//覐΂ƏՓ˂�������Ԃ�

private:
	HitChecker(const HitChecker&);		//�R�s�[�R���X�g���N�^

	void Decision(Player* player);				//�e�]���̔���
	void DecisionEnd(ScoreEarn* scoreEarn);		//����I��

	EffectManager* effectManager;		//�G�t�F�N�g�}�l�[�W���[�̃|�C���^
	Evaluation* evaluation;				//�]��UI�N���X�̃|�C���^

	float distance;						//����
	bool hit;							//覐΂ƏՓ˂�����
	bool excellent;						//excellent��������
	bool miss;							//miss��������
	bool great;							//great��������
	bool good;							//good��������
	bool decisionFlag;					//���肵����
	bool decision[2];
	//�萔
	const int   DECISION_START_LINE;	//����J�n���C��
	const int   DECISION_END_LINE;		//����I�����C��
	const float RADIUS_EXCELLENT;		//excellent�͈̔�
	const float RADIUS_GREAT;			//great�͈̔�
	const float RADIUS_GOOD;			//good�͈̔�
	const float RADIUS_MISS;			//miss�͈̔�
};