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

	void EvaluationUi(int evaluationGraph);
	void Draw(PlayScene::State state, int frame);

private:
	UiManager(const UiManager&);		//コピーコンストラクタ

	void StartGameDraw();

	static const std::string FOLLDER_PATH;			//画像格納フォルダ
	static const std::string UI_GRAPHIC_PATH;		//UI画像
	static const std::string FILENAME_EXTENSION;	// 拡張子

	//画像の種類
	enum Graphic
	{
		NOMAL = 0,
		START,
		GAME,
		GRAPHIC_AMOUNT
	};

	//画像ハンドル
	int uiHandle[GRAPHIC_AMOUNT];

};