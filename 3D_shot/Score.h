#pragma once

//シングルトン
class Score final
{
public:

	static Score& GetInstance();		// アドレスを返す

	void Activate();

	//トータルスコア
	void SetScore(int totalScore);
	int  GetScore() { return score; }

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

	int score;
	int excellent;
	int great;
	int good;
	int miss;
};