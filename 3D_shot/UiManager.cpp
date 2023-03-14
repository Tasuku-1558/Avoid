#include "UiManager.h"

using std::string;

const string UiManager::FOLDER_PATH		   = "Data/image/";		//画像ファイルのパス
const string UiManager::UI_GRAPHIC_PATH    = "ui";				//UI画像
const string UiManager::FILENAME_EXTENSION = ".png";			//画像拡張子


/// <summary>
/// コンストラクタ
/// </summary>
UiManager::UiManager()
	: uiHandle()
	, fever(false)
{
	Initialize();
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
	string path = FOLDER_PATH + UI_GRAPHIC_PATH; //フォルダパス + ファイル名
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

/// <summary>
/// 描画処理
/// </summary>
/// <param name="gameState"></param>
/// <param name="font"></param>
/// <param name="countDown"></param>
/// <param name="score"></param>
/// <param name="wave"></param>
void UiManager::Draw(PlayScene::GameState gameState, int font, int countDown, int score, int wave)
{
	switch (gameState)
	{
	case PlayScene::GameState::START:
		StartGameDraw();
		break;

	case PlayScene::GameState::GAME:
		FrameDraw();
		GameUIDraw(font, countDown, score, wave);
		
		break;

	case PlayScene::GameState::FINALWAVE:
		FrameDraw();
		GameUIDraw(font, countDown, score, wave);
		fever = true;
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

/// <summary>
/// 制限時間、スコアの枠描画処理
/// </summary>
void UiManager::FrameDraw()
{
	DrawGraph(0, -150, uiHandle[FRAME], TRUE);
}

/// <summary>
/// フィーバーモードUIの描画
/// </summary>
void UiManager::FeverImageDraw()
{
	if (fever)
	{
		DrawRotaGraph(950, 950, 1.5f, 0, uiHandle[FEVER_IMAGE], TRUE);
	}
}