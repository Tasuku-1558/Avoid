#pragma once

#include "DxLib.h"
#include "PlayScene.h"

#include <string>		//文字列型クラス

class UiManager final
{
public:
	 UiManager();
	~UiManager();

	void Initialize();
	void Finalize();

	
	void Draw(PlayScene::State state, int frame , float feverGauge);

private:
	UiManager(const UiManager&);		//コピーコンストラクタ

	void StartGameDraw();
	void FeverGaugeDraw(float feverGauge);

	//静的定数
	static const std::string FOLDER_PATH;			//画像格納フォルダ
	static const std::string UI_GRAPHIC_PATH;		//UI画像
	static const std::string FILENAME_EXTENSION;	//画像拡張子

	//画像の種類
	enum Graphic
	{
		EXCELLENT,
		GREAT,
		GOOD,
		MISS,
		FEVER_GAUGE,
		GRAPHIC_AMOUNT
	};

	//画像ハンドル
	int uiHandle[GRAPHIC_AMOUNT];
	
};