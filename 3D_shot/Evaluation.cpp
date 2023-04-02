#include "Evaluation.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
Evaluation::Evaluation()
	: evaluationGraph()
	, slowScreenGraph(0)
	, scale(0.0f)
	, displayTime(0.0f)
	, ui(Ui::NOMAL)
	, IMAGE_FOLDER_PATH("Data/Image/")
	, EXCELLENT_PATH("ExcellentEffect.png")
	, GREAT_PATH("GreatEffect.png")
	, GOOD_PATH("GoodEffect.png")
	, MISS_PATH("MissEffect.png")
	, SLOW_SCREEN_PATH("SlowScreen.png")
	, EVALUATION_NUMBER(4)
	, MAX_SCALE(1.0f)
	, MAX_DISPLAY_TIME(50.0f)
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
	//評価画像の読み込み
	evaluationGraph[0] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, EXCELLENT_PATH).c_str());

	evaluationGraph[1] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, GREAT_PATH).c_str());

	evaluationGraph[2] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, GOOD_PATH).c_str());

	evaluationGraph[3] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, MISS_PATH).c_str());

	//集中線画像の読み込み
	slowScreenGraph	= LoadGraph(InputPath(IMAGE_FOLDER_PATH, SLOW_SCREEN_PATH).c_str());
}

/// <summary>
/// 画像のパスを入力
/// </summary>
/// <param name="folderPath">フォルダまでのパス</param>
/// <param name="imagePath">画像のパス</param>
/// <returns></returns>
string Evaluation::InputPath(string folderPath, string imagePath)
{
	return string(folderPath + imagePath);
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
		displayTime += 1.0f;

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