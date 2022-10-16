#include "TitleScene.h"
#include "DxLib.h"

const int TitleScene::TitleNameX = 600;
const int TitleScene::TitleNameY = 500;


TitleScene::TitleScene():SceneBase(SceneType::TITLE)
	, TitleImage(0)
	, TitleBackgroundX(0)
	, TitleBackgroundY(0)
{
	//�����Ȃ�
}

TitleScene::~TitleScene()
{
	//�����Ȃ�
}

void TitleScene::Initialize()
{
	TitleImage = LoadGraph("data/Image/TitleBackground.png");
}

SceneType TitleScene::Update(float deltaTime)
{
	//���̃V�[����
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

	//�C�[�W���O����
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

//�����𖾖�
void TitleScene::Blink()
{
	// ���Ń��[�`��
	static int Alpha = 0;
	static int Inc = 5;

	if (Alpha > 255 && Inc > 0)
		Inc *= -1;

	if (Alpha < 0 && Inc < 0)
		Inc *= -1;

	Alpha += Inc;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
	DrawFormatString(200, 700, GetColor(255, 0, 0), "Push Space Key To GameStart!");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, Alpha);
}

void TitleScene::Draw()
{
	DrawGraph(TitleBackgroundX, TitleBackgroundY, TitleImage, TRUE);

	ChangeFont("�l�r ����");	//��ނ�MS�����ɕύX
	SetFontSize(110);			//�����̃t�H���g�T�C�Y�ύX

	DrawString(TitleNameX, TitleNameY, TitleName, GetColor(170, 200, 200));

	Blink();
}