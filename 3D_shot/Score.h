#pragma once

//シングルトン
class Score final
{
public:

	static Score& GetInstance();		// アドレスを返す

	void Activate();

	//トータルスコア
	void SetScore(int totalScore);
	int  GetScore() { return targetScore; }

	//各スコアの数
	void SetExcellentCount(int totalExcellent);
	int  GetExcellentCount() { return excellent; }

	void SetGreatCount(int totalGreat);
	int  GetGreatCount() { return great; }

	void SetGoodCount(int totalGood);
	int  GetGoodCount() { return good; }

	void SetMissCount(int totalMiss);
	int  GetMissCount() { return miss; }


private:

	 Score();
	 Score(const Score&);		//コピーコンストラクタ
	~Score();

	void Scoring();				//スコアを目標スコアに足し引き

	int score;
	int excellent;
	int great;
	int good;
	int miss;
	int targetScore;
};