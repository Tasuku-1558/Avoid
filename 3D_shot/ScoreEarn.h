#pragma once

class Score;

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
	int score;								//獲得スコア
	int excellentCount;						//excellentの数
	int greatCount;							//greatの数
	int goodCount;							//goodの数
	int missCount;							//missの数
	

	//静的定数
	static const int   SCORE_GOOD;			//goodのスコア
	static const int   SCORE_GREAT;			//greatのスコア
	static const int   SCORE_EXCELLENT;		//excellentのスコア
	static const int   SCORE_MISS;			//missのスコア
	static const int   FIRST_SCORE;			//スコアの初期値
};