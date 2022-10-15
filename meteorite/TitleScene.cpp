#include "TitleScene.h"
#include "DxLib.h"


TitleScene::TitleScene():SceneBase(SceneType::TITLE)
	, TitleImage(0)
	, TitleBackgroundX(0)
	, TitleBackgroundY(0)
{
	//処理なし
}

TitleScene::~TitleScene()
{
	//処理なし
}

void TitleScene::Initialize()
{
	TitleImage = LoadGraph("data/Image/TitleBackground.png");
}

SceneType TitleScene::Update(float deltaTime)
{
	if (CheckHitKey(KEY_INPUT_G))
	{
		TitleBackgroundX += 13-TitleBackgroundY;
		TitleBackgroundY += 13+TitleBackgroundX;
	}
	//次のシーンへ
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		NowSceneType = SceneType::PLAY;
	}
	
	return NowSceneType;
}

void TitleScene::TitleNameMove()
{
	if (StartTitleCount < 1.0f)
	{
		StartTitleCount += 0.01f;
	}

	if (StartTitleCount > 1.0f)
	{
		StartTitleCount = 1.0f;
	}

	for (int i = 0; i < 1; i++)
	{
		TitleAnimTime[i] += 0.01f;

		if (TitleAnimTime[i] > 1.0f)
		{
			TitleAnimTime[i] = 1.0f;
		}
	}

	//イージング処理
	for (int i = 0; i < 1; i++)
	{
		float Time = TitleAnimTime[i];
		if (Time < 0.0f)
		{
			Time = 0.0f;
		}

		//TitleNowPos[i] = EaseInExponential();
	}
}

void TitleScene::Draw()
{
	DrawGraph(TitleBackgroundX, TitleBackgroundY, TitleImage, TRUE);


}
