#pragma once


class Score final
{
public:

	static Score& GetInstance();// アドレスを返す


	void SetScore(int scoreT);
	int  GetScore() { return score; }

private:

	 Score();
	 Score(const Score&);
	~Score();

	int score;
};