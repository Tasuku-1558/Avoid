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

	//int GetScore() { return score; }
	/*int GetExcellent() { return excellentCount; }
	int GetGreat() { return greatCount; }
	int GetGood() { return goodCount; }
	int GetMiss() { return missCount; }*/

private:
	int score;								//獲得スコア
	int excellentCount;
	int greatCount;
	int goodCount;
	int missCount;
	

	//静的定数
	static const int   SCORE_GOOD;			//goodのスコア
	static const int   SCORE_GREAT;			//greatのスコア
	static const int   SCORE_EXCELLENT;		//excellentのスコア
	static const int   SCORE_MISS;			//missのスコア
	static const int   FIRST_SCORE;			//スコアの初期値
};