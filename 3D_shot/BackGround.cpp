#include "BackGround.h"

const string BackGround::VIDEO_FOLDER_PATH		= "Data/Video/";		//Videoフォルダまでのパス
const string BackGround::BACK_GROUND_VIDEO_PATH = "BackGround_.mp4";	//背景動画のパス


/// <summary>
/// コンストラクタ
/// </summary>
BackGround::BackGround()
	: backGroundHandle(0)
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
BackGround::~BackGround()
{
	Finalize();
}

void BackGround::Initialize()
{
	string failePath = VIDEO_FOLDER_PATH + BACK_GROUND_VIDEO_PATH;
	backGroundHandle = LoadGraph(failePath.c_str());
}

/// <summary>
/// 終了処理
/// </summary>
void BackGround::Finalize()
{
	PauseMovieToGraph(backGroundHandle);

	DeleteGraph(backGroundHandle);
}

/// <summary>
/// 更新処理
/// </summary>
void BackGround::Update()
{
	//背景動画を再生中
	if (!GetMovieStateToGraph(backGroundHandle))
	{
		//動画が終了したら5000秒の所からまた再生する
		SeekMovieToGraph(backGroundHandle, 5000);

		//動画を再生する
		PlayMovieToGraph(backGroundHandle);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void BackGround::Draw()
{
	//背景動画を再生する
	DrawGraph(0, 0, backGroundHandle, FALSE);
}