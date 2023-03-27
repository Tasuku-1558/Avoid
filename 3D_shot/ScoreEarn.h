#pragma once

/// <summary>
/// スコア計算クラス
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


	const int GetScore() { return targetScore; }				//スコアを返す
	const int GetExcellentCount() { return excellentCount; }
	const int GetGreatCount() { return greatCount; }
	const int GetGoodCount() { return goodCount; }
	const int GetMissCount() { return missCount; }

private:
	ScoreEarn(const ScoreEarn&);	//コピーコンストラクタ

	void Scoring();

	int score;					//獲得スコア
	int targetScore;			//目標スコア
	int excellentCount;			//excellentの数
	int greatCount;				//greatの数
	int goodCount;				//goodの数
	int missCount;				//missの数
	

	//定数
	const int SCORE_EXCELLENT;		//excellentのスコア
	const int SCORE_GREAT;			//greatのスコア
	const int SCORE_GOOD;			//goodのスコア
	const int SCORE_MISS;			//missのスコア
};