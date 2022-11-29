#include "Score.h"


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
	score = 0;
	excellent = 0;
	great = 0;
	good = 0;
	miss = 0;
}

void Score::SetScore(int totalScore)
{
	score = totalScore;
	Scoring();
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

//�X�R�A��ڕW�X�R�A�ɑ�������
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