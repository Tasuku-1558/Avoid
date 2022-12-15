#pragma once

#include "DxLib.h"
#include "PlayScene.h"
#include <string>		//文字列型クラス

//UI管理クラス
class UiManager final
{
public:
	 UiManager();
	~UiManager();

	void Initialize();
	void Finalize();

	void Draw(PlayScene::State state, int frame, int font, int countDown, int score, int wave);


private:
	UiManager(const UiManager&);		//コピーコンストラクタ
	
	void StartGameDraw();
	void FrameDraw();					//フレームUIの描画
	void FeverImageDraw();				//フィーバーモードUIの描画
	void GameUIDraw(int font, int countDown, int score, int wave);

	//静的定数
	static const std::string FOLDER_PATH;			//画像格納フォルダ
	static const std::string UI_GRAPHIC_PATH;		//UI画像
	static const std::string FILENAME_EXTENSION;	//画像拡張子

	//画像の種類
	enum Graphic
	{
		FRAME,
		FEVER_IMAGE,
		GRAPHIC_AMOUNT
	};

	//画像ハンドル
	int uiHandle[GRAPHIC_AMOUNT];
};