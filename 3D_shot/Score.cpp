#include "Score.h"


const int Score::FIRST_SCORE = 0;		//�X�R�A�̏����l

Score::Score()
	: score(0)
	, miss(0)
	, excellent(0)
	, great(0)
	, good(0)
	, targetScore(0)
{
	//�����Ȃ�
}

Score::~Score()
{
	//�����Ȃ�
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
/// �ڕW�X�R�A�܂ŃX�R�A�𑫂�����
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