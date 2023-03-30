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

	void Draw();

	//評価の種類
	enum class Ui
	{
		NOMAL,		//通常状態
		EXCELLENT,	//excellent評価
		GREAT,		//great評価
		GOOD,		//good評価
		MISS,		//miss評価
	};

	enum class Ui ui;		//評価の種類

private:

	Evaluation(const Evaluation&);			//コピーコンストラクタ

	void Initialize();						//初期化処理
	void Finalize();						//終了処理
	void ImageMove(int evaluationGraph);	//評価文字の動き
	void EvaluationDraw();					//各評価の描画処理
	void SlowImageDraw();					//速度低速時の集中線の描画処理

	string InputPath(string folderPath,
					 string imagePath);		//画像のパスを入力

	int evaluationGraph[5];					//評価文字の格納用
	int slowScreenGraph;					//速度低速時の集中線
	float waitTime;							//評価文字の表示時間
	float scale;							//評価文字の大きさ


	//定数
	const string IMAGE_FOLDER_PATH;	//Imageフォルダまでのパス
	const string EXCELLENT_PATH;	//excellent画像のパス
	const string GREAT_PATH;		//great画像のパス
	const string GOOD_PATH;			//good画像のパス
	const string MISS_PATH;			//miss画像のパス
	const string SLOW_SCREEN_PATH;	//集中線画像のパス
	const int	 EVALUATION_NUMBER;	//評価文字数

};