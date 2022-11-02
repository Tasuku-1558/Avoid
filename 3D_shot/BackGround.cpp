#include "BackGround.h"


const float  BackGround::SIZE			  = 4000.0f;					//ÉÇÉfÉãî{ó¶
const VECTOR BackGround::INITIAL_POSITION = { 0.0f, 300.0f, 1200.0f };	//èâä˙à íu


BackGround::BackGround()
	: position()
	, backGroundHandle(0)
{
	//èàóùÇ»Çµ
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
	backGroundHandle = LoadGraph("data/image/GameBackground.png");
}

void BackGround::Finalize()
{
	DeleteGraph(backGroundHandle);
	backGroundHandle = NULL;
}

void BackGround::Activate()
{
	position = INITIAL_POSITION;
}

void BackGround::Draw()
{
	DrawBillboard3D(position, 0.5f, 0.5f, SIZE, 0.0f, backGroundHandle, TRUE);
}