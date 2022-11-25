#pragma once

class Score;

class EarnScore final
{
public:
	 EarnScore();
	~EarnScore();

	void Activate();
	void Finalize();
	
	void UpdateMiss();
	void UpdateExcellent();
	void UpdateGreat();
	void UpdateGood();

	bool aa() { return a; }

private:
	int score;								//�l���X�R�A
	int excellentCount;						//excellent�̐�
	int greatCount;							//great�̐�
	int goodCount;							//good�̐�
	int missCount;							//miss�̐�
	bool a;
	

	//�ÓI�萔
	static const int   SCORE_GOOD;			//good�̃X�R�A
	static const int   SCORE_GREAT;			//great�̃X�R�A
	static const int   SCORE_EXCELLENT;		//excellent�̃X�R�A
	static const int   SCORE_MISS;			//miss�̃X�R�A
	static const int   FIRST_SCORE;			//�X�R�A�̏����l
};