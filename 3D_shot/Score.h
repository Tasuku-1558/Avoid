#pragma once

//シングルトン
class Score final
{
public:

	static Score& GetInstance();		// アドレスを返す

	//トータルスコア
	void SetScore(int scoreT);
	int  GetScore() { return score; }

	void SetMissScore(int scoreM);
	int  GetMissScore() { return missScore; }

private:

	 Score();
	 Score(const Score&);		//コピーコンストラクタ
	~Score();

	int score;
	int missScore;
};