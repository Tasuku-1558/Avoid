#include "BackGround.h"


const float  BackGround::SIZE			  = 4000.0f;					//モデル倍率
const VECTOR BackGround::INITIAL_POSITION = { 0.0f, 300.0f, 1200.0f };	//初期位置


BackGround::BackGround()
	: position()
	, backGroundHandle(0)
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
	//backGroundHandle = LoadGraph("data/image/GameBackground.png");
	backGroundHandle = LoadGraph("data/Moon.mp4");
}

void BackGround::Finalize()
{
	DeleteGraph(backGroundHandle);
	backGroundHandle = NULL;
}

void BackGround::Activate()
{
	//position = INITIAL_POSITION;
	
	SeekMovieToGraph(backGroundHandle, 0);


	// ムービーを再生状態に
	PlayMovieToGraph(backGroundHandle);

}

void BackGround::Draw()
{
	//DrawBillboard3D(position, 0.5f, 0.5f, SIZE, 0.0f, backGroundHandle, TRUE);

	if (GetMovieStateToGraph(backGroundHandle == 0))
	{
		DrawGraph(0, 0, backGroundHandle, FALSE);
		
	}
}