#include "ScoreEarn.h"

/// <summary>
/// コンストラクタ
/// </summary>
ScoreEarn::ScoreEarn()
	: score(0)
	, targetScore(0)
	, excellentCount(0)
	, greatCount(0)
	, goodCount(0)
	, missCount(0)
	, SCORE_EXCELLENT(600)
	, SCORE_GREAT(300)
	, SCORE_GOOD(100)
	, SCORE_MISS(300)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
ScoreEarn::~ScoreEarn()
{
	//処理なし
}

/// <summary>
/// 更新処理
/// </summary>
void ScoreEarn::Update()
{
	Scoring();
}

void ScoreEarn::UpdateMiss()
{
	score -= SCORE_MISS;
	missCount++;
}

void ScoreEarn::UpdateExcellent()
{
	score += SCORE_EXCELLENT;
	excellentCount++;
}

void ScoreEarn::UpdateGreat()
{
	score += SCORE_GREAT;
	greatCount++;
}

void ScoreEarn::UpdateGood()
{
	score += SCORE_GOOD;
	goodCount++;
}

void ScoreEarn::Scoring()
{
	//目標スコアになるまでスコアを足し引きする
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