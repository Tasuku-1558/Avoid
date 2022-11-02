#include "UiManager.h"

using std::string;

const string UiManager::FOLLDER_PATH = "data/image/";		//画像ファイルのパス
const string UiManager::UI_GRAPHIC_PATH = "";


UiManager::UiManager()
	: uiHandle()
{
	//処理なし
}

UiManager::~UiManager()
{
	//終了処理が呼ばれてなければ
	if (uiHandle != NULL)
	{
		Finalize();
	}
}

void UiManager::Initialize()
{
}

void UiManager::Finalize()
{
}

void UiManager::EvaluationUi(int evaluationGraph)
{
}

void UiManager::Draw(PlayScene::State state, int frame)
{
}

void UiManager::StartGameDraw()
{
}
