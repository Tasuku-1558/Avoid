#pragma once

class Score;

/// <summary>
/// スコア計測クラス
/// </summary>
class ScoreEarn final
{
public:
	ScoreEarn();
	virtual ~ScoreEarn();
	
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
	

	//定数
	static const int SCORE_GOOD;			//goodのスコア
	static const int SCORE_GREAT;			//greatのスコア
	static const int SCORE_EXCELLENT;		//excellentのスコア
	static const int SCORE_MISS;			//missのスコア
};