#include "TitleScene.h"
#include "DxLib.h"
#include "SceneManager.h"


const string TitleScene::VIDEO_FOLDER_PATH = "data/video/";		//video�t�H���_�܂ł̃p�X
const string TitleScene::IMAGE_FOLDER_PATH = "data/image/";		//image�t�H���_�܂ł̃p�X
const string TitleScene::PLAY_VIDEO_PATH   = "PlayVideo.mp4";	//�^�C�g������̃p�X
const string TitleScene::TITLENAME_PATH	   = "titleName.png";	//�^�C�g�����̉摜�̃p�X
const string TitleScene::TITLE_UI_PATH     = "titleUi.png";		//�v���C�V�[���֑J�ڃL�[��UI�̃p�X


TitleScene::TitleScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, backGroundHandle(0)
	, titleName(0)
	, titleUi(0)
	, alpha(0)
	, inc(0)
	, frame(0.0f)
{
	//�����Ȃ�
}

TitleScene::~TitleScene()
{
	Finalize();
}

void TitleScene::Initialize()
{
	string failePath = VIDEO_FOLDER_PATH + PLAY_VIDEO_PATH;
	backGroundHandle = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + TITLENAME_PATH;
	titleName = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + TITLE_UI_PATH;
	titleUi = LoadGraph(failePath.c_str());
}

void TitleScene::Finalize()
{
	PauseMovieToGraph(backGroundHandle);

	DeleteGraph(backGroundHandle);

	DeleteGraph(titleName);

	DeleteGraph(titleUi);
}

void TitleScene::Activate()
{
	alpha = 255;
	inc = -1;
}

void TitleScene::Update(float deltaTime)
{
	//�f��������Đ�
	if (!GetMovieStateToGraph(backGroundHandle))
	{
		SeekMovieToGraph(backGroundHandle, 5000);

		PlayMovieToGraph(backGroundHandle);
	}

	//�v���C��ʂ�
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		parent->SetNextScene(SceneManager::PLAY);
		return;
	}
}

/// <summary>
/// �����̓_��
/// </summary>
void TitleScene::Blink()
{
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

	DrawGraph(250, 450, titleName, TRUE);
	
	Blink();
}