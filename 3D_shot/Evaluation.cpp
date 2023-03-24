#include "Evaluation.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
Evaluation::Evaluation()
	: evaluationGraph()
	, slowScreenGraph(0)
	, scale(0.0f)
	, waitTime(0.0f)
	, ui(Ui::NOMAL)
	, IMAGE_FOLDER_PATH("Data/image/")
	, EXCELLENT_PATH("ExcellentEffect.png")
	, GREAT_PATH("GreatEffect.png")
	, GOOD_PATH("GoodEffect.png")
	, MISS_PATH("MissEffect.png")
	, SLOW_SCREEN_PATH("SlowScreen.png")
	, EVALUATION_NUMBER(4)
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
/// <param name="folderPath"></param>
/// <param name="imagePath"></param>
/// <returns></returns>
std::string Evaluation::InputPath(std::string folderPath, std::string imagePath)
{
	return std::string(folderPath + imagePath);
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
void Evaluation::SlowImageDraw()
{
	DrawGraph(0, 0, slowScreenGraph, TRUE);
}

/// <summary>
/// 評価文字の動き
/// </summary>
/// <param name="evaluationGraph">評価画像格納</param>
void Evaluation::ImageMove(int evaluationGraph)
{
	DrawRotaGraph(500, 500, scale, 0, evaluationGraph, TRUE);

	scale += 0.9f;

	//文字の大きさを大きくする
	if (scale > 1.0f)
	{
		scale = 1.0f;
		waitTime += 1.0f;

		//表示時間が経過したら
		if (waitTime > 30.0f)
		{
			//通常状態に
			ui = Ui::NOMAL;

			//サイズと表示時間を初期化
			scale = 0.0f;
			waitTime = 0.0f;
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
		SlowImageDraw();
		ImageMove(evaluationGraph[0]);
		break;

	case Ui::GREAT:
		SlowImageDraw();
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