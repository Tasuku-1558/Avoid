#include "TitleScene.h"
#include "DxLib.h"
#include "SceneManager.h"


TitleScene::TitleScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, titleImage(0)
	, titleBackgroundX(0)
	, titleBackgroundY(0)
	, titleName(0)
	, titleUi(0)
{
	//�����Ȃ�
}

TitleScene::~TitleScene()
{
	//�����Ȃ�
}

void TitleScene::Initialize()
{
	titleImage = LoadGraph("data/image/TitleBackground.png");
	titleName = LoadGraph("data/image/TitleName.png");
	titleUi = LoadGraph("data/image/TitleUI.png");
}

void TitleScene::Finalize()
{
}

void TitleScene::Activate()
{
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
	
	DrawGraph(500, 700, titleUi, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

void TitleScene::Draw()
{
	DrawGraph(titleBackgroundX, titleBackgroundY, titleImage, TRUE);

	DrawGraph(350, 450, titleName, TRUE);
	
	Blink();
}