#include "Score.h"


Score::Score()
	: score(0)
	, missScore(0)
{
	//ˆ—‚È‚µ
}

Score::~Score()
{
	//ˆ—‚È‚µ
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