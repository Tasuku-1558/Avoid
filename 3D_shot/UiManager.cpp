#include "UiManager.h"
#include "DxLib.h"

/// <summary>
/// コンストラクタ
/// </summary>
UiManager::UiManager()
	: uiHandle()
	, numberGraphicHandle()
	, alpha(255)
	, inc(-1)
	, displayTime(0)
	, alphaEnd(false)
	, MAX_ALPHA(255)
	, MAX_DISPLAY_TIME(400)
	, INC_SPEED(-1)
	, COUNTDOWN_IMAGE_NUMBER(3)
	, WAVE_CATEGORY(4)
	, IMAGE_FOLDER_PATH("Data/Image/")
	, UI_GRAPHIC_PATH("ui")
	, COUNTDOWN_GRAPHIC_PATH("CountDown")
	, IMAGE_FILENAME_EXTENSION(".png")
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
UiManager::~UiManager()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void UiManager::Initialize()
{
	//Ui画像読み込み
	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		string uiPath = IMAGE_FOLDER_PATH + UI_GRAPHIC_PATH + to_string(i) + IMAGE_FILENAME_EXTENSION;
		uiHandle[i] = LoadGraph(uiPath.c_str());

		if (uiHandle[i] < 0)
		{
			printfDx("Ui画像読み込みに失敗[%d]\n", i);
		}
	}

	//数字画像読み込み
	string numberPath = IMAGE_FOLDER_PATH + COUNTDOWN_GRAPHIC_PATH + IMAGE_FILENAME_EXTENSION;
	LoadDivGraph(numberPath.c_str(), 3, 3, 1, 466, 467, numberGraphicHandle);

	if (numberGraphicHandle[0] < 0)
	{
		printfDx("数字画像読み込みに失敗\n");
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
		WaveDraw(countDown);
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
/// ウェーブ描画
/// </summary>
/// <param name="countDown">ゲーム内時間</param>
void UiManager::WaveDraw(int countDown)
{
	displayTime++;

	Wave w[] =
	{
		{80,WAVE2},
		{60,WAVE3},
		{40,WAVE4},
		{20,FINAL_WAVE},
	};

	for (int i = 0; i < WAVE_CATEGORY; i++)
	{
		if (countDown == w[i].time && displayTime > MAX_DISPLAY_TIME)
		{
			WaveAlpha(w[i].graphic);
		}
	}
}

/// <summary>
/// ウェーブ画像の透過処理
/// </summary>
/// <param name="graphic">Ui画像の種類</param>
void UiManager::WaveAlpha(Graphic graphic)
{
	if (alpha > MAX_ALPHA && inc > 0)
	{
		inc *= INC_SPEED;
	}

	//透過が終わったら
	if (alpha == inc)
	{
		alphaEnd = true;
	}

	alpha += inc;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawGraph(0, 90, uiHandle[graphic], TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

/// <summary>
/// 透過の初期化
/// </summary>
void UiManager::AlphaReset()
{
	alphaEnd = false;
	alpha = MAX_ALPHA;
	displayTime = 0;
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