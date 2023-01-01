#pragma once

#include <string>

using namespace std;

/// <summary>
/// 評価の種類
/// </summary>
enum class UI
{
	NOMAL,
	EXCELLENT,
	GREAT,
	GOOD,
	MISS,
};

/// <summary>
/// 評価UIクラス
/// </summary>
class Evaluation final
{
public:
	 Evaluation();
	~Evaluation();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(int evaluationGraph);
	void Draw();

	enum class UI ui;

private:

	void EvaluationUi();					//各評価の描画処理
	void SlowUi();							//速度低速時の集中線の描画処理

	//各評価文字の格納用
	int excellentGraph;
	int greatGraph;
	int goodGraph;
	int missGraph;

	int slowScreenGraph;					//速度低速時の集中線
	float waitTime;							//評価文字の表示時間
	float scale;							//評価文字の大きさ


	//静的定数
	static const string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const string EXCELLENT_PATH;		//excellent画像のパス
	static const string GREAT_PATH;			//great画像のパス
	static const string GOOD_PATH;			//good画像のパス
	static const string MISS_PATH;			//miss画像のパス
	static const string SLOW_SCREEN_PATH;	//集中線画像のパス

};