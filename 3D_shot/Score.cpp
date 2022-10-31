#include "Score.h"


Score::Score()
	: score(0)
	, missScore(0)
{
	//処理なし
}

Score::~Score()
{
	//処理なし
}

Score& Score::GetInstance()
{
	static Score score;
	return score;
}

void Score::SetScore(int scoreT)
{
	score = scoreT;
}

void Score::SetMissScore(int scoreM)
{
	missScore = scoreM;
}