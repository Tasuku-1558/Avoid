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
	, TARGET_SCORE_INCREASE(100)
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

/// <summary>
/// missのスコア
/// </summary>
void ScoreEarn::MissScore()
{
	score -= SCORE_MISS;
	missCount++;
}

/// <summary>
/// excellentのスコア
/// </summary>
void ScoreEarn::ExcellentScore()
{
	score += SCORE_EXCELLENT;
	excellentCount++;
}

/// <summary>
/// greatのスコア
/// </summary>
void ScoreEarn::GreatScore()
{
	score += SCORE_GREAT;
	greatCount++;
}

/// <summary>
/// goodのスコア
/// </summary>
void ScoreEarn::GoodScore()
{
	score += SCORE_GOOD;
	goodCount++;
}

/// <summary>
/// スコア計算
/// </summary>
void ScoreEarn::Scoring()
{
	//目標スコアになるまでスコアを足し引きする
	if (score != targetScore)
	{
		if (score > targetScore)
		{
			targetScore += TARGET_SCORE_INCREASE;
		}
		else
		{
			targetScore -= TARGET_SCORE_INCREASE;
		}
	}
}