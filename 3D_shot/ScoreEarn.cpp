#include "ScoreEarn.h"

/// <summary>
/// �R���X�g���N�^
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
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ScoreEarn::~ScoreEarn()
{
	//�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
void ScoreEarn::Update()
{
	Scoring();
}

/// <summary>
/// miss�̃X�R�A
/// </summary>
void ScoreEarn::MissScore()
{
	score -= SCORE_MISS;
	missCount++;
}

/// <summary>
/// excellent�̃X�R�A
/// </summary>
void ScoreEarn::ExcellentScore()
{
	score += SCORE_EXCELLENT;
	excellentCount++;
}

/// <summary>
/// great�̃X�R�A
/// </summary>
void ScoreEarn::GreatScore()
{
	score += SCORE_GREAT;
	greatCount++;
}

/// <summary>
/// good�̃X�R�A
/// </summary>
void ScoreEarn::GoodScore()
{
	score += SCORE_GOOD;
	goodCount++;
}

/// <summary>
/// �X�R�A�v�Z
/// </summary>
void ScoreEarn::Scoring()
{
	//�ڕW�X�R�A�ɂȂ�܂ŃX�R�A�𑫂���������
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