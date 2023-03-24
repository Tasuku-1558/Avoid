#pragma once

#include "Math3D.h"
#include "EffectManager.h"
#include <vector>

class Meteorite;
class Player;
class Evaluation;
class ScoreEarn;

using namespace std;

/// <summary>
/// �q�b�g�`�F�b�J�[�N���X
/// </summary>
class HitChecker final
{
public:
	HitChecker(EffectManager* const inEffect);
	virtual ~HitChecker();

	void PlayerAndMeteorite(Player* player, vector<Meteorite*>* meteorite, 
							Evaluation* evaluation, ScoreEarn* scoreEarn);		//�v���C���[�ƃG�l�~�[�̏Փ˔���

	const bool Hit() { return hit; }

private:
	HitChecker(const HitChecker&);			//�R�s�[�R���X�g���N�^

	void MissDecision(Evaluation* evaluation, Player* player);	//miss����
	void ExcellentDecision(Evaluation* evaluation);				//excellent����
	void GreatDecision(Evaluation* evaluation);					//great����
	void GoodDecision(Evaluation* evaluation);					//good����
	

	EffectManager* effectManager;			//�G�t�F�N�g�}�l�[�W���[�̃|�C���^

	bool hit;								//覐΂ƏՓ˂�����
	bool excellent;							//excellent��������
	bool miss;								//miss��������
	bool great;								//great��������
	bool good;								//good��������
	bool decisionFlag;						//���肵����

	//�萔
	const float RADIUS_EXCELLENT;		//excellent�͈̔�
	const float RADIUS_GREAT;			//great�͈̔�
	const float RADIUS_GOOD;			//good�͈̔�
	const float RADIUS_MISS;			//miss�͈̔�
	const int   SCORE_DECISION_LINE;	//�X�R�A���胉�C��
	const int   DECISION_END_LINE;		//����I�����C��
};