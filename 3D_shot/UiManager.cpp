#include "UiManager.h"
#include "DxLib.h"

/// <summary>
/// コンストラクタ
/// </summary>
UiManager::UiManager()
	: uiHandle()
	, numberImage()
	, alpha(255)
	, inc(-1)
	, displayTime(0)
	, alphaEnd(false)
	, MAX_ALPHA(255)
	, MAX_DISPLAY_TIME(400)
	, INITIAL_DISPLAY_TIME(0)
	, INC_SPEED(-1)
	, GAME_UI_NUMBER(3)
	, COUNTDOWN_IMAGE_NUMBER(3)
	, WAVE_CATEGORY(4)
	, WAVE2_TIME(80)
	, WAVE3_TIME(60)
	, WAVE4_TIME(40)
	, WAVE5_TIME(20)
	, TOTAL_COUNT(3)
	, LANDSCAPE_COUNT(3)
	, PORTRAIT_COUNT(1)
	, SIZE_X(466)
	, SIZE_Y(467)
	, NUMBER_IMAGE_POS_X(720)
	, NUMBER_IMAGE_POS_Y(300)
	, WAVE_IMAGE_POS_X(0)
	, WAVE_IMAGE_POS_Y(90)
	, TIME_UI_POS_X(500)
	, SCORE_UI_POS_X(1000)
	, WAVE_UI_POS_X(100)
	, GAME_UI_POS_Y(100)
	, FRAME_IMAGE_POS_X(0)
	, FRAME_IMAGE_POS_Y(-150)
	, TIME_UI_COLOR(GetColor(255, 0, 0))
	, SCORE_UI_COLOR(GetColor(255, 255, 0))
	, WAVE_UI_COLOR(GetColor(0, 255, 0))
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
	LoadDivGraph(numberPath.c_str(), TOTAL_COUNT, LANDSCAPE_COUNT, PORTRAIT_COUNT, SIZE_X, SIZE_Y, numberImage);

	if (numberImage[0] < 0)
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
		DeleteGraph(numberImage[i]);
		numberImage[i] = NULL;
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

	DrawGraph(NUMBER_IMAGE_POS_X, NUMBER_IMAGE_POS_Y, numberImage[number], TRUE);
}

/// <summary>
/// ウェーブ描画
/// </summary>
/// <param name="countDown">ゲーム内時間</param>
void UiManager::WaveDraw(int countDown)
{
	displayTime++;

	Wave wave[] =
	{
		{WAVE2_TIME, WAVE2},
		{WAVE3_TIME, WAVE3},
		{WAVE4_TIME, WAVE4},
		{WAVE5_TIME, FINAL_WAVE},
	};

	for (int i = 0; i < WAVE_CATEGORY; i++)
	{
		if (countDown == wave[i].time && displayTime > MAX_DISPLAY_TIME)
		{
			WaveAlpha(wave[i].graphic);
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

	DrawGraph(WAVE_IMAGE_POS_X, WAVE_IMAGE_POS_Y, uiHandle[graphic], TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

/// <summary>
/// 透過の初期化
/// </summary>
void UiManager::AlphaReset()
{
	alphaEnd = false;
	alpha = MAX_ALPHA;
	displayTime = INITIAL_DISPLAY_TIME;
}

/// <summary>
/// ゲームUi文字描画
/// </summary>
/// <param name="font">ゲームフォント</param>
/// <param name="countDown">ゲーム内時間</param>
/// <param name="score">獲得スコア</param>
/// <param name="wave">ウェーブ</param>
void UiManager::GameUiDraw(int font, int countDown, int score, int wave)
{
	GameUi gameUi[] =
	{
		{TIME_UI_POS_X,  TIME_UI_COLOR,  "TIME : %d",  countDown},
		{SCORE_UI_POS_X, SCORE_UI_COLOR, "SCORE : %d", score},
		{WAVE_UI_POS_X,  WAVE_UI_COLOR,  "WAVE : %d",  wave},
	};

	for (int i = 0; i < GAME_UI_NUMBER; i++)
	{
		//ゲームUi文字の表示
		DrawFormatStringToHandle(gameUi[i].posX, GAME_UI_POS_Y, gameUi[i].color, font, gameUi[i].name, gameUi[i].uiType);
	}
}

/// <summary>
/// 枠描画
/// </summary>
void UiManager::FrameDraw()
{
	DrawGraph(FRAME_IMAGE_POS_X, FRAME_IMAGE_POS_Y, uiHandle[FRAME], TRUE);
}