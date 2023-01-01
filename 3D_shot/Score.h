#pragma once


/// <summary>
/// スコア分配クラス
/// </summary>
class Score final
{
public:

	static Score& GetInstance();		// アドレスを返す

	void Activate();

	//スコアの合計
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

	void Scoring();				//目標スコアまでスコアを足し引き
private:

	 Score();					//コンストラクタ
	 Score(const Score&);		//コピーコンストラクタ
	~Score();					//デストラクタ

	//各スコア格納用
	int score;
	int excellent;
	int great;
	int good;
	int miss;

	int targetScore;	//目標スコアまでスコアを足し引きする

	//静的定数
	static const int   FIRST_SCORE;			//スコアの初期値

};