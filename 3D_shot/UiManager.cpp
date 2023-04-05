#include "UiManager.h"
#include "DxLib.h"

/// <summary>
/// コンストラクタ
/// </summary>
UiManager::UiManager()
	: uiHandle()
	, numberGraphicHandle()
	, COUNTDOWN_IMAGE_NUMBER(3)
	, FOLDER_PATH("Data/Image/")
	, UI_GRAPHIC_PATH("ui")
	, COUNTDOWN_GRAPHIC_PATH("CountDown")
	, FILENAME_EXTENSION(".png")
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
UiManager::~UiManager()
{
	//終了処理が呼ばれてなければ
	if (uiHandle[0] != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// 初期化処理
/// </summary>
void UiManager::Initialize()
{
	//UI画像読み込み
	string path = FOLDER_PATH + UI_GRAPHIC_PATH;	//フォルダパス + ファイル名
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

	//数字画像読み込み
	fullPath = FOLDER_PATH + COUNTDOWN_GRAPHIC_PATH + FILENAME_EXTENSION;
	LoadDivGraph(fullPath.c_str(), 3, 3, 1, 466, 467, numberGraphicHandle);

	if (numberGraphicHandle[0] < 0)
	{
		printfDx("画像読み込みに失敗_UiManager_number\n");
	}
}

/// <summary>
/// 終了処理
/// </summary>
void UiManager::Finalize()
{
	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		DeleteGraph(uiHandle[i]);
		uiHandle[i] = NULL;
	}

	for (int i = 0; i < COUNTDOWN_IMAGE_NUMBER; ++i)
	{
		DeleteGraph(numberGraphicHandle[i]);
		numberGraphicHandle[i] = NULL;
	}
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="gameState">ゲームの状態</param>
/// <param name="frame">フレーム数</param>
/// <param name="font">ゲームフォント</param>
/// <param name="countDown">ゲーム内時間</param>
/// <param name="score">獲得スコア</param>
/// <param name="wave">ウェーブ</param>
void UiManager::Draw(GameScene::GameState gameState, float frame, int font, int countDown, int score, int wave)
{
	switch (gameState)
	{
	case GameScene::GameState::START:
		StartCountDraw(frame);
		break;

	case GameScene::GameState::GAME:
		FrameDraw();
		GameUiDraw(font, countDown, score, wave);
		break;
	}
}

/// <summary>
/// カウントダウン描画
/// </summary>
/// <param name="frame">フレーム数</param>
void UiManager::StartCountDraw(float frame)
{
	int number = (int)frame;

	DrawGraph(720, 300, numberGraphicHandle[number], TRUE);
}

/// <summary>
/// ゲーム内UI描画
/// </summary>
/// <param name="font">ゲームフォント</param>
/// <param name="countDown">ゲーム内時間</param>
/// <param name="score">獲得スコア</param>
/// <param name="wave">ウェーブ</param>
void UiManager::GameUiDraw(int font, int countDown, int score, int wave)
{
	//制限時間表示
	DrawFormatStringToHandle(500, 100, GetColor(255, 0, 0), font, "TIME : %d", countDown);

	//獲得スコア表示
	DrawFormatStringToHandle(1000, 100, GetColor(255, 255, 0), font, "SCORE : %d", score);

	//隕石のウェーブ表示
	DrawFormatStringToHandle(100, 100, GetColor(0, 255, 0), font, "WAVE : %d", wave);
}

/// <summary>
/// 枠描画
/// </summary>
void UiManager::FrameDraw()
{
	DrawGraph(0, -150, uiHandle[FRAME], TRUE);
}