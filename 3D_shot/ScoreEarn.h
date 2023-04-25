#pragma once

/// <summary>
/// スコア計算クラス
/// </summary>
class ScoreEarn final
{
public:
	ScoreEarn();
	virtual ~ScoreEarn();

	void Update();				//更新処理
	
	void MissScore();			//missのスコア
	void ExcellentScore();		//excellentのスコア
	void GreatScore();			//greatのスコア
	void GoodScore();			//goodのスコア

	const int GetScore() { return targetScore; }				//スコアを返す
	const int GetExcellentCount() { return excellentCount; }	//excellentの回数を返す
	const int GetGreatCount() { return greatCount; }			//greatの回数を返す
	const int GetGoodCount() { return goodCount; }				//goodの回数を返す
	const int GetMissCount() { return missCount; }				//missの回数を返す

private:
	ScoreEarn(const ScoreEarn&);	//コピーコンストラクタ

	void Scoring();			//スコア計算

	int score;				//獲得スコア
	int targetScore;		//目標スコア
	int excellentCount;		//excellentの数
	int greatCount;			//greatの数
	int goodCount;			//goodの数
	int missCount;			//missの数
	
	//定数
	const int SCORE_EXCELLENT;			//excellentのスコア
	const int SCORE_GREAT;				//greatのスコア
	const int SCORE_GOOD;				//goodのスコア
	const int SCORE_MISS;				//missのスコア
	const int TARGET_SCORE_INCREASE;	//目標スコアの増加量
};