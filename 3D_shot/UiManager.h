#pragma once

#include "GameScene.h"
#include <string>

using namespace std;

/// <summary>
/// UI管理クラス
/// </summary>
class UiManager final
{
public:
	UiManager();
	virtual ~UiManager();

	void Draw(GameScene::GameState gameState, 
			  float frame, 
			  int font, 
			  int countDown, 
			  int score, 
			  int wave);	//描画処理

	void AlphaReset();		//透過の初期化

	const bool AlphaEnd() { return alphaEnd; }	//透過が終了したかを返す

private:
	UiManager(const UiManager&);		//コピーコンストラクタ

	//画像の種類
	enum Graphic
	{
		FRAME,			//枠画像
		WAVE2,			//ウェーブ2画像
		WAVE3,			//ウェーブ3画像
		WAVE4,			//ウェーブ4画像
		FINAL_WAVE,		//最終ウェーブ画像
		GRAPHIC_AMOUNT,	//画像の数
	};

	struct Wave
	{
		int time;			//画像を表示する時間
		Graphic graphic;	//画像の種類
	};

	struct GameUi
	{
		int posX;			//ゲームUiのX座標
		unsigned int color;	//ゲームUiのカラー
		char name[30];		//ゲームUiのスコア名
		int uiType;			//ゲームUiの種類
	};
	
	void Initialize();						//初期化処理
	void Finalize();						//終了処理
	void StartCountDraw(float frame);		//カウントダウン描画
	void GameUiDraw(int font, int countDown, int score, int wave);		//ゲームUi文字描画
	void FrameDraw();						//枠描画
	void WaveDraw(int countDown);			//ウェーブ描画
	void WaveAlpha(Graphic graphic);		//ウェーブ画像の透過処理

	int uiHandle[GRAPHIC_AMOUNT];			//画像ハンドル格納用
	int numberImage[3];						//カウントダウン画像格納用
	int alpha;								//透過度
	int inc;								//透過スピ―ド
	int displayTime;						//ウェーブ画像表示時間
	bool alphaEnd;							//透過終了フラグ

	//定数
	const int MAX_ALPHA;					//最大透過度
	const int MAX_DISPLAY_TIME;				//最大ウェーブ画像表示時間
	const int INITIAL_DISPLAY_TIME;			//初期のウェーブ画像表示時間
	const int INC_SPEED;					//透過スピード
	const int GAME_UI_NUMBER;				//表示するゲームUiの数
	const int COUNTDOWN_IMAGE_NUMBER;		//カウントダウン画像の配列数
	const int WAVE_CATEGORY;				//ウェーブ画像の種類
	const int WAVE2_TIME;					//ウェーブ2画像を表示する時間
	const int WAVE3_TIME;					//ウェーブ3画像を表示する時間
	const int WAVE4_TIME;					//ウェーブ4画像を表示する時間
	const int WAVE5_TIME;					//ウェーブ5画像を表示する時間
	const int TOTAL_COUNT;					//カウントダウン画像の総数
	const int LANDSCAPE_COUNT;				//カウントダウン画像の横向きの総数
	const int PORTRAIT_COUNT;				//カウントダウン画像の縦向きの総数
	const int SIZE_X;						//カウントダウン画像の一枚あたりの横サイズ
	const int SIZE_Y;						//カウントダウン画像の縦サイズ
	const int NUMBER_IMAGE_POS_X;			//カウントダウン画像のX座標
	const int NUMBER_IMAGE_POS_Y;			//カウントダウン画像のY座標
	const int WAVE_IMAGE_POS_X;				//ウェーブ画像のX座標
	const int WAVE_IMAGE_POS_Y;				//ウェーブ画像のY座標
	const int TIME_UI_POS_X;				//制限時間UiのX座標
	const int SCORE_UI_POS_X;				//獲得スコアUiのX座標
	const int WAVE_UI_POS_X;				//ウェーブUiのX座標
	const int GAME_UI_POS_Y;				//ゲームUiのY座標
	const int FRAME_IMAGE_POS_X;			//枠画像のX座標
	const int FRAME_IMAGE_POS_Y;			//枠画像のY座標

	const unsigned int TIME_UI_COLOR;		//制限時間Uiのカラー
	const unsigned int SCORE_UI_COLOR;		//獲得スコアUiのカラー
	const unsigned int WAVE_UI_COLOR;		//ウェーブUiのカラー

	const string IMAGE_FOLDER_PATH;			//画像格納フォルダ
	const string UI_GRAPHIC_PATH;			//Ui画像
	const string COUNTDOWN_GRAPHIC_PATH;	//数字画像ファイルのパス
	const string IMAGE_FILENAME_EXTENSION;	//画像拡張子
};