#include "BackGround.h"

const string BackGround::VIDEO_FOLDER_PATH		= "data/video/";		//videoフォルダまでのパス
const string BackGround::BACK_GROUND_VIDEO_PATH = "BackGround_.mp4";		//背景動画のパス

BackGround::BackGround()
	: backGroundHandle(0)
{
	//処理なし
}

BackGround::~BackGround()
{
	Finalize();
}

void BackGround::Initialize()
{
	string failePath = VIDEO_FOLDER_PATH + BACK_GROUND_VIDEO_PATH;
	backGroundHandle = LoadGraph(failePath.c_str());
}

void BackGround::Finalize()
{
	DeleteGraph(backGroundHandle);
	backGroundHandle = NULL;
}

void BackGround::Activate()
{
	//処理なし
}

void BackGround::Draw()
{
	DrawGraph(0, 0, backGroundHandle, FALSE);

	//プレイ画面の動画を再生
	if (!GetMovieStateToGraph(backGroundHandle))
	{
		SeekMovieToGraph(backGroundHandle, 5000);

		PlayMovieToGraph(backGroundHandle);
	}
}