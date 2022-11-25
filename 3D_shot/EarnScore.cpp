#include "EarnScore.h"
#include "Score.h"

const int	EarnScore::SCORE_GOOD	   = 100;		//good�̃X�R�A
const int	EarnScore::SCORE_GREAT	   = 300;		//great�̃X�R�A
const int	EarnScore::SCORE_EXCELLENT = 600;		//excellent�̃X�R�A
const int	EarnScore::SCORE_MISS	   = 300;		//miss�̃X�R�A
const int	EarnScore::FIRST_SCORE	   = 0;			//�X�R�A�̏����l


EarnScore::EarnScore()
	: score(0)
	, excellentCount(0)
	, greatCount(0)
	, goodCount(0)
	, missCount(0)
	, a(false)
{
	//�����Ȃ�
}

EarnScore::~EarnScore()
{
	//�����Ȃ�
}

void EarnScore::Activate()
{
	score = FIRST_SCORE;
	excellentCount = FIRST_SCORE;
	greatCount = FIRST_SCORE;
	goodCount = FIRST_SCORE;
	missCount = FIRST_SCORE;
	a = false;
}

void EarnScore::Finalize()
{
}

void EarnScore::UpdateMiss()
{
	score -= SCORE_MISS;
	Score::GetInstance().SetScore(score);

	missCount++;
	Score::GetInstance().SetMissCount(missCount);

	a = true;
}

void EarnScore::UpdateExcellent()
{
	score += SCORE_EXCELLENT;
	Score::GetInstance().SetScore(score);

	excellentCount++;
	Score::GetInstance().SetExcellentCount(excellentCount);

	a = true;
}

void EarnScore::UpdateGreat()
{
	score += SCORE_GREAT;
	Score::GetInstance().SetScore(score);

	greatCount++;
	Score::GetInstance().SetGreatCount(greatCount);

	a = true;
}

void EarnScore::UpdateGood()
{
	score += SCORE_GOOD;
	Score::GetInstance().SetScore(score);

	goodCount++;
	Score::GetInstance().SetGoodCount(goodCount);

	a = true;
}