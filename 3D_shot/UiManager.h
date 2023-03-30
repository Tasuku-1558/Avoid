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

	void Draw(GameScene::GameState gameState, int font, int countDown, int score, int wave);	//描画処理

private:

	UiManager(const UiManager&);		//コピーコンストラクタ

	//画像の種類
	enum Graphic
	{
		FRAME,			//枠画像
		FEVER_IMAGE,
		GRAPHIC_AMOUNT,	//画像の数
	};
	
	void Initialize();			//初期化処理
	void Finalize();			//終了処理
	void StartGameDraw();
	void GameUIDraw(int font, int countDown, int score, int wave);		//ゲーム内UI描画
	void FrameDraw();					//枠描画
	void FeverImageDraw();				//フィーバーモードUIの描画
	

	int uiHandle[GRAPHIC_AMOUNT];		//画像ハンドル格納用
	bool fever;


	//定数
	const string FOLDER_PATH;			//画像格納フォルダ
	const string UI_GRAPHIC_PATH;		//UI画像
	const string FILENAME_EXTENSION;	//画像拡張子
	
};