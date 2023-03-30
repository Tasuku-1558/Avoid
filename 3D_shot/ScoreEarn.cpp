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
			targetScore += 100;
		}
		else
		{
			targetScore -= 100;
		}
	}
}