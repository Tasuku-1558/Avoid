#include "Evaluation.h"
#include "DxLib.h"


Evaluation::Evaluation()
	: excellentGraph(0)
	, greatGraph(0)
	, goodGraph(0)
	, missGraph(0)
	, slowGraph(0)
	, scale(0.0f)
	, waitTime(0.0f)
{
	ui = UI::Nomal;
}

Evaluation::~Evaluation()
{
	//ˆ—‚È‚µ
}

void Evaluation::Initialize()
{
	excellentGraph = LoadGraph("data/image/ExcellentEffect.png");
	greatGraph	   = LoadGraph("data/image/GreatEffect.png");
	goodGraph	   = LoadGraph("data/image/GoodEffect.png");
	missGraph	   = LoadGraph("data/image/MissEffect.png");
	slowGraph	   = LoadGraph("data/image/SlowScreen3.png");
}

void Evaluation::Finalize()
{
	DeleteGraph(excellentGraph);
	DeleteGraph(greatGraph);
	DeleteGraph(goodGraph);
	DeleteGraph(missGraph);
	DeleteGraph(slowGraph);
}

void Evaluation::Activate()
{
	ui = UI::Nomal;
}

void Evaluation::Update(int evaluationGraph)
{
	DrawRotaGraph(500, 500, scale, 0, evaluationGraph, TRUE);

	scale += 0.9f;

	if (scale > 1.0f)
	{
		scale = 1.0f;
		waitTime += 1.0f;

		if (waitTime > 30.0f)
		{
			ui = UI::Nomal;
			scale = 0.0f;
			waitTime = 0.0f;
		}
	}
}

void Evaluation::SlowUi()
{
	DrawGraph(0, 0, slowGraph, TRUE);
}

void Evaluation::EvaluationUi()
{
	switch (ui)
	{
	case UI::Excellent:
		Update(excellentGraph);
		SlowUi();
		break;

	case UI::Great:
		Update(greatGraph);
		SlowUi();
		break;

	case UI::Good:
		Update(goodGraph);
		break;
		
	case UI::Miss:
		Update(missGraph);
		break;
	}
}

void Evaluation::Draw()
{
	EvaluationUi();
}