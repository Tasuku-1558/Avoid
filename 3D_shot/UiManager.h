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

	void Draw(GameScene::GameState gameState, float frame, int font, int countDown, int score, int wave);	//描画処理

private:

	UiManager(const UiManager&);		//コピーコンストラクタ

	//画像の種類
	enum Graphic
	{
		FRAME,			//枠画像
		GRAPHIC_AMOUNT,	//画像の数
	};
	
	void Initialize();			//初期化処理
	void Finalize();			//終了処理
	void StartCountDraw(float frame);		//カウントダウン描画
	void GameUiDraw(int font, int countDown, int score, int wave);		//ゲーム内UI描画
	void FrameDraw();					//枠描画

	int uiHandle[GRAPHIC_AMOUNT];		//画像ハンドル格納用
	int numberGraphicHandle[3];			//カウントダウン画像格納用

	//定数
	const string FOLDER_PATH;				//画像格納フォルダ
	const string UI_GRAPHIC_PATH;			//UI画像
	const string COUNTDOWN_GRAPHIC_PATH;	//数字画像ファイルのパス
	const string FILENAME_EXTENSION;		//画像拡張子
	const int	 COUNTDOWN_IMAGE_NUMBER;	//カウントダウン画像の配列数
	
};