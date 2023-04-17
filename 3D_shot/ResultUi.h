#pragma once

#include <string>

using namespace std;

/// <summary>
/// リザルト画面UIクラス
/// </summary>
class ResultUi final
{
public:
	ResultUi();
	virtual ~ResultUi();

	void Draw(int scoreFont, 
			  int countFont, 
			  int score, 
			  int excellentCount, 
			  int greatCount, 
			  int goodCount, 
			  int missCount);	//描画処理

private:
	ResultUi(const ResultUi&);	//コピーコンストラクタ

	void Initialize();			//初期化処理
	void Blink();				//文字の点滅
	void ScoreDraw(int scoreFont, int countFont, int score, int excellentCount, int greatCount, int goodCount, int missCount);	//スコア表示
	void GaugeDraw(int score);	//ゲージ表示

	struct Score
	{
		int maxDisplayTime;	//最大スコア表示時間
		int posY;			//スコアのY座標
		unsigned int color;	//スコアの色
		int font;			//ゲームフォント
		char name[30];		//スコア名
		int scoreType;		//スコアの種類
	};

	int displayTime;			//スコア表示時間
	int evaluationImage[3];		//スコア評価
	int gaugeFrame;				//ゲージ枠格納用
	int resultUi;				//遷移のUI画像格納用
	int alpha;					//透過度
	int inc;					//透過スピ―ド
	float scoreGauge;			//スコアゲージ
	float earnScore;			//獲得スコア
	bool displayFlag;			//評価画像表示フラグ
	

	//定数
	const int	 DECISION_B_LINE;		//B評価判定ライン
	const int	 DECISION_A_LINE;		//A評価判定ライン
	const int	 DECISION_S_LINE;		//S評価判定ライン
	const int	 EVALUATION_NUMBER;		//評価文字数
	const int	 SCORE_DRAW_NUMBER;		//表示するスコア数
	const int	 MAX_ALPHA;				//最大透過度
	const int	 INC_SPEED;				//透過スピード
	const unsigned int ORANGE;			//ゲージのカラー
	const float  MAX_SCORE_GAUGE;		//最大スコアゲージ
	const float  GAUGE_INCREASE;		//スコア増加量
	const string IMAGE_FOLDER_PATH;		//Imageフォルダまでのパス
	const string RESULT_UI_PATH;		//遷移のUI画像のパス
	const string GAUGE_FRAME_PATH;		//ゲージ枠画像のパス
	const string SCORE_B_PATH;			//B評価画像のパス
	const string SCORE_A_PATH;			//A評価画像のパス
	const string SCORE_S_PATH;			//S評価画像のパス
};