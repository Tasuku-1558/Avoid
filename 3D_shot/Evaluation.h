#pragma once

#include <string>

using namespace std;

/// <summary>
/// 評価UIクラス
/// </summary>
class Evaluation final
{
public:
	Evaluation();
	virtual ~Evaluation();

	//評価の種類
	enum class Ui
	{
		NOMAL,		//通常状態
		EXCELLENT,	//excellent評価
		GREAT,		//great評価
		GOOD,		//good評価
		MISS,		//miss評価
	};

	void Draw();	//描画処理

	enum class Ui ui;	//評価の種類

private:
	Evaluation(const Evaluation&);			//コピーコンストラクタ

	void Initialize();						//初期化処理
	void Finalize();						//終了処理
	void ImageMove(int evaluationGraph);	//評価文字の動き
	void EvaluationDraw();					//各評価の描画処理
	void SlowScreenDraw();					//速度低速時の集中線の描画処理

	int evaluationGraph[5];					//評価文字画像の格納用
	int slowScreenGraph;					//集中線画像の格納用
	float displayTime;						//表示時間
	double scale;							//評価文字の大きさ

	struct EvaluationImage
	{
		string evaluationPath;	//評価画像のパス
	};

	//定数
	const int	 EVALUATION_NUMBER;		//評価文字数
	const int	 SLOW_SCREEN_IMAGE_X;	//集中線画像のX座標
	const int	 SLOW_SCREEN_IMAGE_Y;	//集中線画像のY座標
	const int	 EVALUATION_IMAGE_X;	//評価文字画像のX座標
	const int	 EVALUATION_IMAGE_Y;	//評価文字画像のY座標

	const float  MAX_DISPLAY_TIME;		//最大表示時間
	const float  INITIAL_DISPLAY_TIME;	//初期の最大表示時間
	const float  DISPLAY_TIME_INCREASE;	//表示時間増加量

	const double MAX_SCALE;				//最大の文字の大きさ
	const double INITIAL_SCALE;			//初期の文字の大きさ
	const double STOP_SCALE;			//止める文字の大きさ
	const double SCALE_INCREASE;		//文字の大きさの増加量
	const double ANGLE;					//評価文字画像の回転値

	const string IMAGE_FOLDER_PATH;		//Imageフォルダまでのパス
	const string EXCELLENT_PATH;		//excellent画像のパス
	const string GREAT_PATH;			//great画像のパス
	const string GOOD_PATH;				//good画像のパス
	const string MISS_PATH;				//miss画像のパス
	const string SLOW_SCREEN_PATH;		//集中線画像のパス
};