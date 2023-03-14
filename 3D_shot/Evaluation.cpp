#include "Evaluation.h"
#include "DxLib.h"

const string Evaluation::IMAGE_FOLDER_PATH = "data/image/";				//imageフォルダまでのパス
const string Evaluation::EXCELLENT_PATH	   = "ExcellentEffect.png";		//excellent画像のパス
const string Evaluation::GREAT_PATH		   = "GreatEffect.png";			//great画像のパス
const string Evaluation::GOOD_PATH		   = "GoodEffect.png";			//good画像のパス
const string Evaluation::MISS_PATH		   = "MissEffect.png";			//miss画像のパス
const string Evaluation::SLOW_SCREEN_PATH  = "SlowScreen.png";			//集中線画像のパス
const int	 Evaluation::EVALUATION_NUMBER = 4;							//評価文字数


/// <summary>
/// コンストラクタ
/// </summary>
Evaluation::Evaluation()
	: evaluationGraph()
	, slowScreenGraph(0)
	, scale(0.0f)
	, waitTime(0.0f)
	, ui(Ui::NOMAL)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Evaluation::~Evaluation()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void Evaluation::Initialize()
{
	//画像の読み込み
	evaluationGraph[0] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, EXCELLENT_PATH).c_str());

	evaluationGraph[1] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, GREAT_PATH).c_str());

	evaluationGraph[2] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, GOOD_PATH).c_str());

	evaluationGraph[3] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, MISS_PATH).c_str());

	slowScreenGraph	   = LoadGraph(InputPath(IMAGE_FOLDER_PATH, SLOW_SCREEN_PATH).c_str());
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
/// 活性化処理
/// </summary>
void Evaluation::Activate()
{
	//処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="evaluationGraph"></param>
void Evaluation::Update(int evaluationGraph)
{
	ImageMove(evaluationGraph);
}

/// <summary>
/// 速度低速時の集中線の描画処理
/// </summary>
void Evaluation::SlowUi()
{
	DrawGraph(0, 0, slowScreenGraph, TRUE);
}

/// <summary>
/// 評価文字の動き
/// </summary>
/// <param name="evaluationGraph"></param>
void Evaluation::ImageMove(int evaluationGraph)
{
	DrawRotaGraph(500, 500, scale, 0, evaluationGraph, TRUE);

	scale += 0.9f;

	//文字の大きさを大きくする
	if (scale > 1.0f)
	{
		scale = 1.0f;
		waitTime += 1.0f;

		if (waitTime > 30.0f)
		{
			ui = Ui::NOMAL;
			scale = 0.0f;
			waitTime = 0.0f;
		}
	}
}

/// <summary>
/// 各評価の描画処理
/// </summary>
void Evaluation::EvaluationUi()
{
	switch (ui)
	{
	case Ui::EXCELLENT:
		SlowUi();
		Update(evaluationGraph[0]);
		break;

	case Ui::GREAT:
		SlowUi();
		Update(evaluationGraph[1]);
		break;

	case Ui::GOOD:
		Update(evaluationGraph[2]);
		break;
		
	case Ui::MISS:
		Update(evaluationGraph[3]);
		break;
	}
}

void Evaluation::Draw()
{
	EvaluationUi();
}