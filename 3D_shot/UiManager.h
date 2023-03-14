#pragma once

#include "DxLib.h"
#include "PlayScene.h"
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

	void Draw(PlayScene::GameState gameState, int font, int countDown, int score, int wave);

private:

	UiManager(const UiManager&);		//コピーコンストラクタ

	//画像の種類
	enum Graphic
	{
		FRAME,			//制限時間フレーム画像
		FEVER_IMAGE,
		GRAPHIC_AMOUNT,	//画像の数
	};
	
	void Initialize();
	void Finalize();
	void StartGameDraw();
	void GameUIDraw(int font, int countDown, int score, int wave);		//ゲーム中のUIの描画
	void FrameDraw();					//制限時間、スコアの枠描画処理
	void FeverImageDraw();				//フィーバーモードUIの描画
	

	//静的定数
	static const string FOLDER_PATH;		//画像格納フォルダ
	static const string UI_GRAPHIC_PATH;	//UI画像
	static const string FILENAME_EXTENSION;	//画像拡張子

	bool fever;
	int uiHandle[GRAPHIC_AMOUNT];					//画像ハンドル格納用
};