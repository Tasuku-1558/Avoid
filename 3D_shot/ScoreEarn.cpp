#include "ScoreEarn.h"
#include "Score.h"

const int	ScoreEarn::SCORE_GOOD	   = 100;		//goodのスコア
const int	ScoreEarn::SCORE_GREAT	   = 300;		//greatのスコア
const int	ScoreEarn::SCORE_EXCELLENT = 600;		//excellentのスコア
const int	ScoreEarn::SCORE_MISS	   = 300;		//missのスコア
const int	ScoreEarn::FIRST_SCORE	   = 0;			//スコアの初期値


ScoreEarn::ScoreEarn()
	: score(0)
	, excellentCount(0)
	, greatCount(0)
	, goodCount(0)
	, missCount(0)
{
	//処理なし
}

ScoreEarn::~ScoreEarn()
{
	//処理なし
}

void ScoreEarn::Activate()
{
	score = FIRST_SCORE;
	excellentCount = FIRST_SCORE;
	greatCount = FIRST_SCORE;
	goodCount = FIRST_SCORE;
	missCount = FIRST_SCORE;
}

void ScoreEarn::Finalize()
{
}

void ScoreEarn::UpdateMiss()
{
	score -= SCORE_MISS;
	Score::GetInstance().SetScore(score);

	missCount++;
	Score::GetInstance().SetMissCount(missCount);
}

void ScoreEarn::UpdateExcellent()
{
	score += SCORE_EXCELLENT;
	Score::GetInstance().SetScore(score);

	excellentCount++;
	Score::GetInstance().SetExcellentCount(excellentCount);
}

void ScoreEarn::UpdateGreat()
{
	score += SCORE_GREAT;
	Score::GetInstance().SetScore(score);

	greatCount++;
	Score::GetInstance().SetGreatCount(greatCount);
}

void ScoreEarn::UpdateGood()
{
	score += SCORE_GOOD;
	Score::GetInstance().SetScore(score);

	goodCount++;
	Score::GetInstance().SetGoodCount(goodCount);
}