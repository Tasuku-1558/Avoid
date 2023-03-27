#pragma once

/// <summary>
/// �X�R�A�v�Z�N���X
/// </summary>
class ScoreEarn final
{
public:
	ScoreEarn();
	virtual ~ScoreEarn();

	void Update();
	
	void UpdateMiss();
	void UpdateExcellent();
	void UpdateGreat();
	void UpdateGood();


	const int GetScore() { return targetScore; }				//�X�R�A��Ԃ�
	const int GetExcellentCount() { return excellentCount; }
	const int GetGreatCount() { return greatCount; }
	const int GetGoodCount() { return goodCount; }
	const int GetMissCount() { return missCount; }

private:
	ScoreEarn(const ScoreEarn&);	//�R�s�[�R���X�g���N�^

	void Scoring();

	int score;					//�l���X�R�A
	int targetScore;			//�ڕW�X�R�A
	int excellentCount;			//excellent�̐�
	int greatCount;				//great�̐�
	int goodCount;				//good�̐�
	int missCount;				//miss�̐�
	

	//�萔
	const int SCORE_EXCELLENT;		//excellent�̃X�R�A
	const int SCORE_GREAT;			//great�̃X�R�A
	const int SCORE_GOOD;			//good�̃X�R�A
	const int SCORE_MISS;			//miss�̃X�R�A
};