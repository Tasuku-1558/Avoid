#include "Evaluation.h"
#include "DxLib.h"
#include "InputManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
Evaluation::Evaluation()
	: ui(Ui::NOMAL)
	, evaluationGraph()
	, slowScreenGraph(0)
	, displayTime(0.0f)
	, scale(0.0)
	, EVALUATION_NUMBER(4)
	, SLOW_SCREEN_IMAGE_X(0)
	, SLOW_SCREEN_IMAGE_Y(0)
	, EVALUATION_IMAGE_X(500)
	, EVALUATION_IMAGE_Y(500)
	, MAX_DISPLAY_TIME(50.0f)
	, INITIAL_DISPLAY_TIME(0.0f)
	, DISPLAY_TIME_INCREASE(1.0f)
	, MAX_SCALE(1.0)
	, INITIAL_SCALE(0.0)
	, STOP_SCALE(1.0)
	, SCALE_INCREASE(0.9)
	, ANGLE(0.0)
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
	EvaluationImage evaluationImage[] =
	{
		{EXCELLENT_PATH},
		{GREAT_PATH},
		{GOOD_PATH},
		{MISS_PATH},
	};

	//評価画像の読み込み
	for (int i = 0; i < EVALUATION_NUMBER; i++)
	{
		evaluationGraph[i] = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, evaluationImage[i].evaluationPath).c_str());
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
	DrawGraph(SLOW_SCREEN_IMAGE_X, SLOW_SCREEN_IMAGE_Y, slowScreenGraph, TRUE);
}

/// <summary>
/// 評価文字の動き
/// </summary>
/// <param name="evaluationGraph">評価文字の画像</param>
void Evaluation::ImageMove(int evaluationGraph)
{
	DrawRotaGraph(EVALUATION_IMAGE_X, EVALUATION_IMAGE_Y, scale, ANGLE, evaluationGraph, TRUE);

	scale += SCALE_INCREASE;

	//目的の大きさになったら
	if (scale > MAX_SCALE)
	{
		scale = STOP_SCALE;
		displayTime += DISPLAY_TIME_INCREASE;

		//目的の表示時間が経過したら
		if (displayTime > MAX_DISPLAY_TIME)
		{
			//通常状態に
			ui = Ui::NOMAL;

			//大きさと表示時間を初期化
			scale = INITIAL_SCALE;
			displayTime = INITIAL_DISPLAY_TIME;
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