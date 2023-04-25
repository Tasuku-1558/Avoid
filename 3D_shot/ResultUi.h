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
	void Blink();				//遷移Ui画像の点滅
	void ScoreDraw(int scoreFont, int countFont, int score, int excellentCount, int greatCount, int goodCount, int missCount);	//スコア表示
	void GaugeDraw(int score);	//ゲージ表示

	struct Score
	{
		int maxDisplayTime;	//最大表示時間
		int posY;			//スコアのY座標
		unsigned int color;	//スコアの色
		int font;			//ゲームフォント
		char name[30];		//スコア名
		int scoreType;		//スコアの種類
	};

	int displayTime;			//スコア表示時間
	int evaluationImage[3];		//スコア評価
	int gaugeFrame;				//ゲージ枠格納用
	int resultUi;				//遷移のUi画像格納用
	int alpha;					//透過度
	int inc;					//透過スピ―ド
	float scoreGauge;			//スコアゲージ
	float earnScore;			//獲得スコア
	bool displayFlag;			//評価画像表示フラグ

	//定数
	const int DECISION_B_LINE;				//B評価判定ライン
	const int DECISION_A_LINE;				//A評価判定ライン
	const int DECISION_S_LINE;				//S評価判定ライン
	const int EVALUATION_NUMBER;			//評価文字数
	const int SCORE_DRAW_NUMBER;			//表示するスコア数
	const int MAX_ALPHA;					//最大透過度
	const int INC_SPEED;					//透過スピード
	const int MAX_SCORE_DISPLAY_TIME;		//最大スコア表示時間
	const int MAX_EXCELLENT_DISPLAY_TIME;	//最大Excellent表示時間
	const int MAX_GREAT_DISPLAY_TIME;		//最大Great表示時間
	const int MAX_GOOD_DISPLAY_TIME;		//最大Good表示時間
	const int MAX_MISS_DISPLAY_TIME;		//最大Miss表示時間
	const int SCORE_POS_X;					//スコアのX座標
	const int SCORE_POS_Y;					//スコアのY座標
	const int EXCELLENT_POS_Y;				//ExcellentのY座標
	const int GREAT_POS_Y;					//GreatのY座標
	const int GOOD_POS_Y;					//GoodのY座標
	const int MISS_POS_Y;					//MissのY座標
	const int EVALUATION_IMAGE_POS_X;		//評価画像のX座標
	const int EVALUATION_IMAGE_POS_Y;		//評価画像のY座標
	const int RESULT_UI_POS_X;				//遷移のUi画像のX座標
	const int RESULT_UI_POS_Y;				//遷移のUi画像のY座標
	const int TOP_LEFT_VERTEX_POS_X;		//左上の頂点X座標
	const int TOP_LEFT_VERTEX_POS_Y;		//左上の頂点Y座標
	const int BOTTOM_RIGHT_VERTEX_POS_X;	//右下の頂点X座標
	const int BOTTOM_RIGHT_VERTEX_POS_Y;	//右下の頂点Y座標
	const int ADD_POS_X;					//左下の頂点X座標に加える値
	const int GAUGE_FRAME_POS_X;			//スコアゲージ枠のX座標
	const int GAUGE_FRAME_POS_Y;			//スコアゲージ枠のY座標

	const unsigned int SCORE_COLOR;			//スコアのカラー
	const unsigned int EXCELLENT_COLOR;		//Excellentのカラー
	const unsigned int GREAT_COLOR;			//Greatのカラー
	const unsigned int GOOD_COLOR;			//Goodのカラー
	const unsigned int MISS_COLOR;			//Missのカラー
	const unsigned int ORANGE;				//ゲージのカラー

	const float MAX_SCORE_GAUGE;			//最大スコアゲージ
	const float GAUGE_INCREASE;				//スコア増加量
	const float SCORE_DIVISION;				//獲得スコアを割る値

	const double EVALUATION_IMAGE_SCALE;	//評価画像の大きさ
	const double EVALUATION_IMAGE_ANGLE;	//評価画像の回転値

	const string IMAGE_FOLDER_PATH;			//Imageフォルダまでのパス
	const string RESULT_UI_PATH;			//遷移のUi画像のパス
	const string GAUGE_FRAME_PATH;			//ゲージ枠画像のパス
	const string SCORE_B_PATH;				//B評価画像のパス
	const string SCORE_A_PATH;				//A評価画像のパス
	const string SCORE_S_PATH;				//S評価画像のパス
};