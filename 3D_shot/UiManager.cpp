#include "UiManager.h"

using std::string;

const string UiManager::FOLDER_PATH		   = "data/image/";		//画像ファイルのパス
const string UiManager::UI_GRAPHIC_PATH    = "ui";				//UI画像
const string UiManager::FILENAME_EXTENSION = ".png";			//画像拡張子


UiManager::UiManager()
	: uiHandle()
{
	//処理なし
}

UiManager::~UiManager()
{
	//終了処理が呼ばれてなければ
	if (uiHandle[0] != NULL)
	{
		Finalize();
	}
}

void UiManager::Initialize()
{
	//UI画像読み込み
	string path = FOLDER_PATH + UI_GRAPHIC_PATH; // フォルダパス + ファイル名
	string fullPath = path;

	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		fullPath = path + std::to_string(i) + FILENAME_EXTENSION;
		uiHandle[i] = LoadGraph(fullPath.c_str());

		if (uiHandle[i] < 0)
		{
			printfDx("画像読み込みに失敗[%d]\n", i);
		}
	}
}

void UiManager::Finalize()
{
	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		DeleteGraph(uiHandle[i]);
		uiHandle[i] = NULL;
	}
}

void UiManager::Draw(PlayScene::State state, int frame,int font, int countDown, int score, int wave)
{
	switch (state)
	{
	case PlayScene::START:
		StartGameDraw();
		break;

	case PlayScene::GAME:
		FrameDraw();
		GameUIDraw(font, countDown, score, wave);
		
		break;

	case PlayScene::FEVER:
		FrameDraw();
		GameUIDraw(font, countDown, score, wave);
		FeverImageDraw();
		break;
	}
}

void UiManager::StartGameDraw()
{
	
}

void UiManager::GameUIDraw(int font, int countDown, int score, int wave)
{
	//制限時間表示
	DrawFormatStringToHandle(500, 100, GetColor(255, 0, 0), font, "TIME : %d", countDown);

	//獲得スコア表示
	DrawFormatStringToHandle(1000, 100, GetColor(255, 255, 0), font, "SCORE : %d", score);

	//隕石のウェーブ表示
	DrawFormatStringToHandle(100, 100, GetColor(0, 255, 0), font, "WAVE : %d", wave);
}

void UiManager::FrameDraw()
{
	DrawGraph(0, -150, uiHandle[FRAME], TRUE);
}

void UiManager::FeverImageDraw()
{
	DrawRotaGraph(950, 950, 1.5f, 0, uiHandle[FEVER_IMAGE], TRUE);
}