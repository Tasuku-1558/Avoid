#include "Score.h"


Score::Score()
	: score(0)
	, miss(0)
	, excellent(0)
	, great(0)
	, good(0)
	, targetScore(0)
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

void Score::Activate()
{
	score = 0;
	excellent = 0;
	great = 0;
	good = 0;
	miss = 0;
	targetScore = 0;
}

void Score::SetScore(int totalScore)
{
	score = totalScore;
}

void Score::SetExcellentCount(int totalExcellent)
{
	excellent = totalExcellent;
}

void Score::SetGreatCount(int totalGreat)
{
	great = totalGreat;
}

void Score::SetGoodCount(int totalGood)
{
	good = totalGood;
}

void Score::SetMissCount(int totalMiss)
{
	miss = totalMiss;
}

//スコアを目標スコアに足し引き
void Score::Scoring()
{
	if (score != targetScore)
	{
		if (score > targetScore)
		{
			targetScore += 100;
		}
		else
		{
			targetScore -= 100;
		}
	}
}