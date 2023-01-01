#include "Evaluation.h"
#include "DxLib.h"

const string Evaluation::IMAGE_FOLDER_PATH = "data/image/";				//image�t�H���_�܂ł̃p�X
const string Evaluation::EXCELLENT_PATH	   = "ExcellentEffect.png";		//excellent�摜�̃p�X
const string Evaluation::GREAT_PATH		   = "GreatEffect.png";			//great�摜�̃p�X
const string Evaluation::GOOD_PATH		   = "GoodEffect.png";			//good�摜�̃p�X
const string Evaluation::MISS_PATH		   = "MissEffect.png";			//miss�摜�̃p�X
const string Evaluation::SLOW_SCREEN_PATH  = "SlowScreen.png";			//�W�����摜�̃p�X


Evaluation::Evaluation()
	: excellentGraph(0)
	, greatGraph(0)
	, goodGraph(0)
	, missGraph(0)
	, slowScreenGraph(0)
	, scale(0.0f)
	, waitTime(0.0f)
{
	ui = UI::NOMAL;
}

Evaluation::~Evaluation()
{
	//�����Ȃ�
}

void Evaluation::Initialize()
{
	string failePath = IMAGE_FOLDER_PATH + EXCELLENT_PATH;
	excellentGraph = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + GREAT_PATH;
	greatGraph = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + GOOD_PATH;
	goodGraph = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + MISS_PATH;
	missGraph = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + SLOW_SCREEN_PATH;
	slowScreenGraph = LoadGraph(failePath.c_str());
}

void Evaluation::Finalize()
{
	DeleteGraph(excellentGraph);
	DeleteGraph(greatGraph);
	DeleteGraph(goodGraph);
	DeleteGraph(missGraph);
	DeleteGraph(slowScreenGraph);
}

void Evaluation::Activate()
{
	ui = UI::NOMAL;
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
			ui = UI::NOMAL;
			scale = 0.0f;
			waitTime = 0.0f;
		}
	}
}

/// <summary>
/// ���x�ᑬ���̏W�����̕`�揈��
/// </summary>
void Evaluation::SlowUi()
{
	DrawGraph(0, 0, slowScreenGraph, TRUE);
}

/// <summary>
/// �e�]���̕`�揈��
/// </summary>
void Evaluation::EvaluationUi()
{
	switch (ui)
	{
	case UI::EXCELLENT:
		SlowUi();
		Update(excellentGraph);
		break;

	case UI::GREAT:
		SlowUi();
		Update(greatGraph);
		break;

	case UI::GOOD:
		Update(goodGraph);
		break;
		
	case UI::MISS:
		Update(missGraph);
		break;
	}
}

void Evaluation::Draw()
{
	EvaluationUi();
}