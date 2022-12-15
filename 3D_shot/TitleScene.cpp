#include "TitleScene.h"
#include "DxLib.h"

#include "SceneManager.h"

TitleScene::TitleScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, backGroundHandle(0)
	, titleName(0)
	, titleUi(0)
{
	//�����Ȃ�
}

TitleScene::~TitleScene()
{
	if (backGroundHandle != NULL)
	{
		Finalize();
	}
}

void TitleScene::Initialize()
{
	backGroundHandle = LoadGraph("data/video/PlayVideo.mp4");
	titleName		 = LoadGraph("data/image/titleName.png");
	titleUi			 = LoadGraph("data/image/titleUi.png");
}

void TitleScene::Finalize()
{
	DeleteGraph(backGroundHandle);
	backGroundHandle = NULL;
}

void TitleScene::Activate()
{
	//���[�r�[���Đ���Ԃ�
	PlayMovieToGraph(backGroundHandle);
}

void TitleScene::Update(float deltaTime)
{
	//���̃V�[����
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		parent->SetNextScene(SceneManager::PLAY);
		return;
	}
}

//�����𖾖�
void TitleScene::Blink()
{
	// ���Ń��[�`��
	static int alpha = 0;
	static int inc = 3;

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
	DrawGraph(0, 0, backGroundHandle, FALSE);

	if (GetMovieStateToGraph(backGroundHandle) == 0)
	{
		SeekMovieToGraph(backGroundHandle, 5000);

		PlayMovieToGraph(backGroundHandle);
	}

	DrawGraph(250, 450, titleName, TRUE);
	
	Blink();
}