#include "Evaluation.h"
#include "DxLib.h"

Evaluation::Evaluation()
	: excellentGraph(0)
	, greatGraph(0)
	, goodGraph(0)
	, missGraph(0)
	, scale(0.0f)
	, count(0.0f)
	, rotation(0)
	, imageHandle(0)
{
	ui = UI::Nomal;
}

Evaluation::~Evaluation()
{
	//ˆ—‚È‚µ
}

void Evaluation::Initialize()
{
	excellentGraph = LoadGraph("data/Image/ExcellentEffect.png");
	greatGraph	   = LoadGraph("data/Image/GreatEffect.png");
	goodGraph	   = LoadGraph("data/Image/GoodEffect.png");
	missGraph	   = LoadGraph("data/Image/MissEffect.png");
}

void Evaluation::Finalize()
{
	DeleteGraph(excellentGraph);
	DeleteGraph(greatGraph);
	DeleteGraph(goodGraph);
}

void Evaluation::Update(int evaluationGraph)
{
	DrawRotaGraph(500, 500, scale, rotation, evaluationGraph, TRUE);

	scale += 0.9f;

	if (scale > 1.0f)
	{
		count += 1.0f;
		scale = 1.0f;

		if (count > 30.0f)
		{
			ui = UI::Nomal;
			scale = 0.0f;
			count = 0.0f;
		}
	}
}

void Evaluation::EvaluationUpdate()
{
	switch (ui)
	{
	case UI::Excellent:
		Update(excellentGraph);
		break;

	case UI::Great:
		Update(greatGraph);
		break;

	case UI::Good:
		Update(goodGraph);
		break;
		
	case UI::Miss:
		Update(missGraph);
		break;

	default:
		break;
	}
}

void Evaluation::Draw()
{
	switch (ui)
	{
	case UI::Excellent:
		Update(excellentGraph);
		break;

	case UI::Great:
		Update(greatGraph);
		break;

	case UI::Good:
		Update(goodGraph);
		break;

	case UI::Miss:
		Update(missGraph);
		break;

	default:
		break;
	}
}