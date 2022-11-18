#include "BackGround.h"


BackGround::BackGround()
	: backGroundHandle(0)
{
	//処理なし
}

BackGround::~BackGround()
{
	if (backGroundHandle != NULL)
	{
		Finalize();
	}
}

void BackGround::Initialize()
{
	backGroundHandle = LoadGraph("data/Moon2.mp4");
}

void BackGround::Finalize()
{
	DeleteGraph(backGroundHandle);
	backGroundHandle = NULL;
}

void BackGround::Activate()
{	
	//ムービーを再生状態に
	PlayMovieToGraph(backGroundHandle);
}

void BackGround::Draw()
{
	DrawGraph(0, 0, backGroundHandle, FALSE);

	if (GetMovieStateToGraph(backGroundHandle) == 0)
	{
		SeekMovieToGraph(backGroundHandle, 5000);

		PlayMovieToGraph(backGroundHandle);
	}
}