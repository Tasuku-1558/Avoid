#include "TitleScene.h"
#include "DxLib.h"
#include "SoundManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
	: SceneBase(SceneType::TITLE)
	, selectState(SelectState::START)
	, titleMovie(0)
	, titleName(0)
	, titleUi(0)
	, alpha(255)
	, inc(-1)
	, frame(0.0f)
	, VIDEO_FOLDER_PATH("Data/Video/")
	, IMAGE_FOLDER_PATH("Data/image/")
	, PLAY_VIDEO_PATH("PlayVideo.mp4")
	, TITLENAME_PATH("titleName.png")
	, TITLE_UI_PATH("titleUi.png")
	, MAX_ALPHA(255)
	, VIDEO_PLAYBACK_POSITION(5000)
{
	Initialize();
	Activate();
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
	PauseMovieToGraph(titleMovie);

	DeleteGraph(titleMovie);

	DeleteGraph(titleName);

	DeleteGraph(titleUi);
}

/// <summary>
/// 初期化処理
/// </summary>
void TitleScene::Initialize()
{
	//動画データの読み込み
	titleMovie = LoadGraph(InputPath(VIDEO_FOLDER_PATH, PLAY_VIDEO_PATH).c_str());

	//タイトル画像UIの読み込み
	titleName = LoadGraph(InputPath(IMAGE_FOLDER_PATH, TITLENAME_PATH).c_str());

	titleUi = LoadGraph(InputPath(IMAGE_FOLDER_PATH, TITLE_UI_PATH).c_str());
}

/// <summary>
/// パスを入力
/// </summary>
/// <param name="folderPath"></param>
/// <param name="path"></param>
/// <returns></returns>
string TitleScene::InputPath(string folderPath, string path)
{
	return string(folderPath + path);
}

/// <summary>
/// 活性化処理
/// </summary>
void TitleScene::Activate()
{
	//タイトルBGMを再生
	SoundManager::GetInstance().PlayBgm(SoundManager::TITLE);
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
		SeekMovieToGraph(titleMovie, VIDEO_PLAYBACK_POSITION);

		//動画を再生する
		PlayMovieToGraph(titleMovie);
	}

	//ゲーム画面へ
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		nowSceneType = SceneType::PLAY;
	}

	return nowSceneType;
}

/// <summary>
/// 文字の点滅
/// </summary>
void TitleScene::Blink()
{
	if (alpha > MAX_ALPHA && inc > 0)
	{
		inc *= -1;
	}

	if (alpha < 0 && inc < 0)
	{
		inc *= -1;
	}

	alpha += inc;
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	
	DrawGraph(400, 700, titleUi, TRUE);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
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
}