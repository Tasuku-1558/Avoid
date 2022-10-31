#include "Score.h"


Score& Score::GetInstance()
{
	static Score score;
	return score;
}

void Score::SetScore(int scoreT)
{
	score = scoreT;
}

Score::Score()
	: score(0)
{
}

Score::~Score()
{
}
