#include "BackGround.h"

const string BackGround::VIDEO_FOLDER_PATH		= "data/video/";		//video�t�H���_�܂ł̃p�X
const string BackGround::BACK_GROUND_VIDEO_PATH = "BackGround_.mp4";		//�w�i����̃p�X

BackGround::BackGround()
	: backGroundHandle(0)
{
	//�����Ȃ�
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
	//�����Ȃ�
}

void BackGround::Draw()
{
	DrawGraph(0, 0, backGroundHandle, FALSE);

	//�v���C��ʂ̓�����Đ�
	if (!GetMovieStateToGraph(backGroundHandle))
	{
		SeekMovieToGraph(backGroundHandle, 5000);

		PlayMovieToGraph(backGroundHandle);
	}
}