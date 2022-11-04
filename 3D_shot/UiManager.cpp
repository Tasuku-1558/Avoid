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

void UiManager::Draw(PlayScene::State state, int frame , float feverGauge)
{
	switch (state)
	{
	case PlayScene::START:
		StartGameDraw();
		break;

	case PlayScene::GAME:
		FeverGaugeDraw(feverGauge);
		break;
	}
}

void UiManager::StartGameDraw()
{
	
}

void UiManager::FeverGaugeDraw(float feverGauge)
{
	DrawLine3D(VGet(-650.0f, -100.0f,0.0f), VGet(-100.0f, -100.0f, 5000.0f), GetColor(255, 0, 0));
	DrawLine3D(VGet(200.0f, 100.0f, 0.0f), VGet(250.0f, 100.0f, -700.0f), GetColor(255, 0, 0));

	//フィーバーゲージ最大値
	float feverMaxGauge = 100.0f;
	
	//フィーバーゲージ表示
	DrawBox(980, 50, 980 + 850 * (feverGauge / feverMaxGauge), 110, GetColor(186, 85, 211), TRUE);
}