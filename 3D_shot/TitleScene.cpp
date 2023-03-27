#include "TitleScene.h"
#include "PreCompiledHeader.h"
#include "Light.h"
#include "Camera.h"
#include "SoundManager.h"
#include "FadeManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
	: SceneBase(SceneType::TITLE)
	, titleState(TitleState::START)
	, titleMovie(0)
	, titleName(0)
	, startUi(0)
	, exitUi(0)
	, alpha(255)
	, inc(-2)
	, frame(0.0f)
	, sceneChangeGame(false)
	, sceneChangeEnd(false)
	, spherePosition({ -360.0f, 0.0f, 0.0f })
	, VIDEO_FOLDER_PATH("Data/Video/")
	, IMAGE_FOLDER_PATH("Data/image/")
	, PLAY_VIDEO_PATH("PlayVideo.mp4")
	, TITLENAME_PATH("titleName.png")
	, START_UI_PATH("titleUi.png")
	, EXIT_UI_PATH("exitUi.png")
	, MAX_ALPHA(255)
	, PLAY_POSITION(5000)
	, START_SPHERE_POSY(90.0f)
	, EXIT_SPHERE_POSY(0.0f)
	, CHANGE_FRAME(2.1f)
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
	PauseMovieToGraph(titleMovie);

	DeleteGraph(titleMovie);

	DeleteGraph(titleName);

	DeleteGraph(startUi);

	DeleteGraph(exitUi);
}

/// <summary>
/// 初期化処理
/// </summary>
void TitleScene::Initialize()
{
	light = new Light();
	light->TitleLight();

	camera = new Camera();

	fadeManager = new FadeManager();

	//動画データの読み込み
	titleMovie = LoadGraph(InputPath(VIDEO_FOLDER_PATH, PLAY_VIDEO_PATH).c_str());

	//タイトルUIの読み込み
	titleName = LoadGraph(InputPath(IMAGE_FOLDER_PATH, TITLENAME_PATH).c_str());

	startUi = LoadGraph(InputPath(IMAGE_FOLDER_PATH, START_UI_PATH).c_str());

	exitUi = LoadGraph(InputPath(IMAGE_FOLDER_PATH, EXIT_UI_PATH).c_str());

	//タイトルBGMを再生
	SoundManager::GetInstance().PlayBgm(SoundManager::TITLE);
}

/// <summary>
/// パスを入力
/// </summary>
/// <param name="folderPath">フォルダまでのパス</param>
/// <param name="path"></param>
/// <returns></returns>
string TitleScene::InputPath(string folderPath, string path)
{
	return string(folderPath + path);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
/// <returns></returns>
SceneType TitleScene::Update(float deltaTime)
{
	//デモ動画を再生
	if (!GetMovieStateToGraph(titleMovie))
	{
		//動画が終了したら5000秒の所からまた再生する
		SeekMovieToGraph(titleMovie, PLAY_POSITION);

		//動画を再生する
		PlayMovieToGraph(titleMovie);
	}

	if (!sceneChangeGame && !sceneChangeEnd)
	{
		ChangeState();
	}

	ReturnScreen(deltaTime);

	return nowSceneType;
}

/// <summary>
/// タイトルの状態の変更
/// </summary>
void TitleScene::ChangeState()
{
	//スタート状態なら
	if (titleState == TitleState::START)
	{
		spherePosition.y = START_SPHERE_POSY;

		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			sceneChangeGame = true;
		}

		//下矢印キーで状態を終了にする
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			titleState = TitleState::EXIT;
		}
	}

	//終了状態なら
	else
	{
		spherePosition.y = EXIT_SPHERE_POSY;

		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			sceneChangeEnd = true;
		}

		//上矢印キーで状態をスタートにする
		if (CheckHitKey(KEY_INPUT_UP))
		{
			titleState = TitleState::START;
		}
	}
}

/// <summary>
/// 画面を遷移する
/// </summary>
/// <param name="deltaTime"></param>
void TitleScene::ReturnScreen(float deltaTime)
{
	if (sceneChangeGame)
	{
		//ゲーム画面へ
		InputScene(deltaTime, SceneType::GAME);
	}

	if (sceneChangeEnd)
	{
		//ゲームを終了する
		InputScene(deltaTime, SceneType::END);
	}
}

/// <summary>
/// シーンを入力
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="sceneType"></param>
void TitleScene::InputScene(float deltaTime, SceneType sceneType)
{
	frame += deltaTime;

	fadeManager->FadeMove();

	//フレーム数が2.1秒経過したら
	if (frame > CHANGE_FRAME)
	{
		//タイトルBGMを停止
		SoundManager::GetInstance().StopBgm();

		nowSceneType = sceneType;
	}
}

/// <summary>
/// 文字の点滅
/// </summary>
void TitleScene::Blink()
{
	if (alpha > MAX_ALPHA && inc > 0 ||
		alpha < 0 && inc < 0)
	{
		inc *= -1;
	}

	alpha += inc;

	//状態によって文字を点滅させる
	if (titleState == TitleState::START)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		DrawGraph(400, 700, startUi, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);

		DrawGraph(400, 850, exitUi, TRUE);
	}
	else
	{
		DrawGraph(400, 700, startUi, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		DrawGraph(400, 850, exitUi, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void TitleScene::Draw()
{
	//デモ動画を再生する
	DrawGraph(0, 0, titleMovie, FALSE);

	//タイトル名描画
	DrawGraph(250, 450, titleName, TRUE);
	
	Blink();

	//3D球体の描画
	DrawSphere3D(spherePosition, 15.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);

	fadeManager->Draw();
}