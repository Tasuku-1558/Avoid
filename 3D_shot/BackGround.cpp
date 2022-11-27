#include "BackGround.h"


BackGround::BackGround()
	: backGroundHandle(0)
{
	//ˆ—‚È‚µ
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
	backGroundHandle = LoadGraph("data/video/BackGround.mp4");
}

void BackGround::Finalize()
{
	DeleteGraph(backGroundHandle);
	backGroundHandle = NULL;
}

void BackGround::Activate()
{	
	//ƒ€[ƒr[‚ğÄ¶ó‘Ô‚É
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