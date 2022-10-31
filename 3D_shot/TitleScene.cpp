#include "TitleScene.h"
#include "DxLib.h"
#include "SceneManager.h"

const int TitleScene::TITLE_NAME_X = 400;
const int TitleScene::TITLE_NAME_Y = 150;


TitleScene::TitleScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, titleImage(0)
	, titleBackgroundX(0)
	, titleBackgroundY(0)
	, titleName(0)
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
	titleName = LoadGraph("data/image/TitleImage.png");
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
	static int Alpha = 0;
	static int Inc = 5;

	if (Alpha > 255 && Inc > 0)
		Inc *= -1;

	if (Alpha < 0 && Inc < 0)
		Inc *= -1;

	Alpha += Inc;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);

	ChangeFont("�l�r ����");	//��ނ�MS�����ɕύX
	SetFontSize(110);			//�����̃t�H���g�T�C�Y�ύX

	DrawFormatString(200, 700, GetColor(255, 0, 0), "Push Space Key To GameStart!");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, Alpha);
}

void TitleScene::Draw()
{
	DrawGraph(titleBackgroundX, titleBackgroundY, titleImage, TRUE);

	DrawGraph(TITLE_NAME_X, TITLE_NAME_Y, titleName, TRUE);

	Blink();
}