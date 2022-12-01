#pragma once

//シングルトン
//スコア分配クラス
class Score final
{
public:

	static Score& GetInstance();		// アドレスを返す

	void Activate();

	//スコア合計
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

	void Scoring();				//スコアを目標スコアに足し引き
private:

	 Score();					//コンストラクタ
	 Score(const Score&);		//コピーコンストラクタ
	~Score();					//デストラクタ

	int score;
	int excellent;
	int great;
	int good;
	int miss;
	int targetScore;
};