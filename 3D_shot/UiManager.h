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

	//
	struct Wave
	{
		int time;			//制限時間
		Graphic graphic;	//画像の種類
	};
	
	void Initialize();						//初期化処理
	void Finalize();						//終了処理
	void StartCountDraw(float frame);		//カウントダウン描画
	void GameUiDraw(int font, int countDown, int score, int wave);		//ゲーム内UI描画
	void FrameDraw();						//枠描画
	void WaveDraw(int countDown);			//ウェーブ描画
	void WaveAlpha(Graphic graphic);		//ウェーブ画像の透過処理

	int uiHandle[GRAPHIC_AMOUNT];		//画像ハンドル格納用
	int numberGraphicHandle[3];			//カウントダウン画像格納用
	int alpha;							//透過度
	int inc;							//透過スピ―ド
	int displayTime;					//ウェーブ画像表示時間
	bool alphaEnd;						//透過終了フラグ

	//定数
	const int	 MAX_ALPHA;					//最大透過度
	const int	 MAX_DISPLAY_TIME;			//最大ウェーブ画像表示時間
	const int	 INC_SPEED;					//透過スピード
	const int	 COUNTDOWN_IMAGE_NUMBER;	//カウントダウン画像の配列数
	const int	 WAVE_CATEGORY;				//ウェーブ画像の種類
	const string IMAGE_FOLDER_PATH;			//画像格納フォルダ
	const string UI_GRAPHIC_PATH;			//UI画像
	const string COUNTDOWN_GRAPHIC_PATH;	//数字画像ファイルのパス
	const string IMAGE_FILENAME_EXTENSION;	//画像拡張子

};