#include "Score.h"


const int Score::FIRST_SCORE = 0;		//スコアの初期値

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
	score		= FIRST_SCORE;
	excellent	= FIRST_SCORE;
	great		= FIRST_SCORE;
	good		= FIRST_SCORE;
	miss		= FIRST_SCORE;
	targetScore = FIRST_SCORE;
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

/// <summary>
/// 目標スコアまでスコアを足し引き
/// </summary>
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