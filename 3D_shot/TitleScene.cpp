#include "TitleScene.h"
#include "DxLib.h"
#include "SoundManager.h"


const string TitleScene::VIDEO_FOLDER_PATH = "data/video/";		//videoフォルダまでのパス
const string TitleScene::IMAGE_FOLDER_PATH = "data/image/";		//imageフォルダまでのパス
const string TitleScene::PLAY_VIDEO_PATH   = "PlayVideo.mp4";	//タイトル動画のパス
const string TitleScene::TITLENAME_PATH	   = "titleName.png";	//タイトル名の画像のパス
const string TitleScene::TITLE_UI_PATH     = "titleUi.png";		//プレイシーンへ遷移キーのUIのパス


/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
	: SceneBase(SceneType::TITLE)
	, titleMovie(0)
	, titleName(0)
	, titleUi(0)
	, alpha(0)
	, inc(0)
	, frame(0.0f)
	, selectState(SelectState::START)
{
	Initialize();
	Activate();
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
	Finalize();
}

void TitleScene::Initialize()
{
	//動画データの読み込み
	string failePath = VIDEO_FOLDER_PATH + PLAY_VIDEO_PATH;
	titleMovie = LoadGraph(failePath.c_str());

	//タイトル画像UIの読み込み
	failePath = IMAGE_FOLDER_PATH + TITLENAME_PATH;
	titleName = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + TITLE_UI_PATH;
	titleUi = LoadGraph(failePath.c_str());
}

void TitleScene::Finalize()
{
	PauseMovieToGraph(titleMovie);

	DeleteGraph(titleMovie);

	DeleteGraph(titleName);

	DeleteGraph(titleUi);
}

void TitleScene::Activate()
{
	alpha = 255;
	inc = -1;

	//タイトルBGMを再生
	SoundManager::GetInstance().PlayBgm(SoundManager::TITLE);
}

SceneType TitleScene::Update(float deltaTime)
{
	//デモ動画を再生
	if (!GetMovieStateToGraph(titleMovie))
	{
		//動画が終了したら0秒の所からまた再生する
		SeekMovieToGraph(titleMovie, 5000);

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
	if (alpha > 255 && inc > 0)
		inc *= -1;

	if (alpha < 0 && inc < 0)
		inc *= -1;

	alpha += inc;
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	
	DrawGraph(400, 700, titleUi, TRUE);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

void TitleScene::Draw()
{
	//デモ動画を再生する
	DrawGraph(0, 0, titleMovie, FALSE);

	//タイトル名描画
	DrawGraph(250, 450, titleName, TRUE);
	
	Blink();
}