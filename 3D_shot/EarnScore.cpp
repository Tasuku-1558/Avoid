#include "EarnScore.h"
#include "Score.h"

const int	EarnScore::SCORE_GOOD	   = 100;		//goodのスコア
const int	EarnScore::SCORE_GREAT	   = 200;		//greatのスコア
const int	EarnScore::SCORE_EXCELLENT = 600;		//excellentのスコア
const int	EarnScore::SCORE_MISS	   = 300;		//missのスコア
const int	EarnScore::FIRST_SCORE	   = 0;			//スコアの初期値


EarnScore::EarnScore()
	: score(0)
	, missScore(0)
{
	//処理なし
}

EarnScore::~EarnScore()
{
	//処理なし
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