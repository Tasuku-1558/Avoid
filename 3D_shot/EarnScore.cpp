#include "EarnScore.h"
#include "Score.h"

const int	EarnScore::SCORE_GOOD	   = 100;		//good�̃X�R�A
const int	EarnScore::SCORE_GREAT	   = 200;		//great�̃X�R�A
const int	EarnScore::SCORE_EXCELLENT = 600;		//excellent�̃X�R�A
const int	EarnScore::SCORE_MISS	   = 300;		//miss�̃X�R�A
const int	EarnScore::FIRST_SCORE	   = 0;			//�X�R�A�̏����l


EarnScore::EarnScore()
	: score(0)
	, missScore(0)
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
}

void EarnScore::Finalize()
{
}

void EarnScore::UpdateMiss()
{
	score -= SCORE_MISS;
	missScore -= SCORE_MISS;
	Score::GetInstance().SetScore(score);
	Score::GetInstance().SetMissScore(missScore);
}

void EarnScore::UpdateExcellent()
{
	score += SCORE_EXCELLENT;
	Score::GetInstance().SetScore(score);
}

void EarnScore::UpdateGreat()
{
	score += SCORE_GREAT;
	Score::GetInstance().SetScore(score);
}

void EarnScore::UpdateGood()
{
	score += SCORE_GOOD;
	Score::GetInstance().SetScore(score);
}