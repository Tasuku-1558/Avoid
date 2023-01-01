#pragma once

class Score;

/// <summary>
/// �X�R�A�l���N���X
/// </summary>
class ScoreEarn final
{
public:
	 ScoreEarn();
	~ScoreEarn();

	void Activate();
	void Finalize();
	
	void UpdateMiss();
	void UpdateExcellent();
	void UpdateGreat();
	void UpdateGood();

private:
	int score;								//�l���X�R�A
	int excellentCount;						//excellent�̐�
	int greatCount;							//great�̐�
	int goodCount;							//good�̐�
	int missCount;							//miss�̐�
	

	//�ÓI�萔
	static const int   SCORE_GOOD;			//good�̃X�R�A
	static const int   SCORE_GREAT;			//great�̃X�R�A
	static const int   SCORE_EXCELLENT;		//excellent�̃X�R�A
	static const int   SCORE_MISS;			//miss�̃X�R�A
	static const int   FIRST_SCORE;			//�X�R�A�̏����l
};