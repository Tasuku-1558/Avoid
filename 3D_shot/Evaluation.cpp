#include "Evaluation.h"
#include "DxLib.h"
#include "InputManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
Evaluation::Evaluation()
	: evaluationGraph()
	, slowScreenGraph(0)
	, scale(0.0f)
	, displayTime(0.0f)
	, ui(Ui::NOMAL)
	, EVALUATION_NUMBER(4)
	, MAX_SCALE(1.0f)
	, MAX_DISPLAY_TIME(50.0f)
	, DISPLAY_TIME_INCREASE(1.0f)
	, IMAGE_FOLDER_PATH("Data/Image/")
	, EXCELLENT_PATH("ExcellentEffect.png")
	, GREAT_PATH("GreatEffect.png")
	, GOOD_PATH("GoodEffect.png")
	, MISS_PATH("MissEffect.png")
	, SLOW_SCREEN_PATH("SlowScreen.png")
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Evaluation::~Evaluation()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void Evaluation::Initialize()
{
	EvaluationImage e[] =
	{
		{EXCELLENT_PATH},
		{GREAT_PATH},
		{GOOD_PATH},
		{MISS_PATH},
	};

	//評価画像の読み込み
	for (int i = 0; i < EVALUATION_NUMBER; i++)
	{
		evaluationGraph[i] = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, e[i].path).c_str());
	}

	//集中線画像の読み込み
	slowScreenGraph	= LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, SLOW_SCREEN_PATH).c_str());
}

/// <summary>
/// 終了処理
/// </summary>
void Evaluation::Finalize()
{
	for (int i = 0; i < EVALUATION_NUMBER; i++)
	{
		DeleteGraph(evaluationGraph[i]);
	}

	DeleteGraph(slowScreenGraph);
}

/// <summary>
/// 速度低速時の集中線の描画処理
/// </summary>
void Evaluation::SlowScreenDraw()
{
	DrawGraph(0, 0, slowScreenGraph, TRUE);
}

/// <summary>
/// 評価文字の動き
/// </summary>
/// <param name="evaluationGraph">評価画像</param>
void Evaluation::ImageMove(int evaluationGraph)
{
	DrawRotaGraph(500, 500, scale, 0, evaluationGraph, TRUE);

	scale += 0.9f;

	//目的の大きさになったら
	if (scale > MAX_SCALE)
	{
		scale = 1.0f;
		displayTime += DISPLAY_TIME_INCREASE;

		//表示時間が経過したら
		if (displayTime > MAX_DISPLAY_TIME)
		{
			//通常状態に
			ui = Ui::NOMAL;

			//サイズと表示時間を初期化
			scale = 0.0f;
			displayTime = 0.0f;
		}
	}
}

/// <summary>
/// 各評価の描画処理
/// </summary>
void Evaluation::EvaluationDraw()
{
	//各評価
	switch (ui)
	{
	case Ui::EXCELLENT:
		SlowScreenDraw();
		ImageMove(evaluationGraph[0]);
		break;

	case Ui::GREAT:
		SlowScreenDraw();
		ImageMove(evaluationGraph[1]);
		break;

	case Ui::GOOD:
		ImageMove(evaluationGraph[2]);
		break;
		
	case Ui::MISS:
		ImageMove(evaluationGraph[3]);
		break;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void Evaluation::Draw()
{
	EvaluationDraw();
}