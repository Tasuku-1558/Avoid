#include "TitleScene.h"
#include "DxLib.h"
#include "SoundManager.h"


const string TitleScene::VIDEO_FOLDER_PATH = "data/video/";		//video�t�H���_�܂ł̃p�X
const string TitleScene::IMAGE_FOLDER_PATH = "data/image/";		//image�t�H���_�܂ł̃p�X
const string TitleScene::PLAY_VIDEO_PATH   = "PlayVideo.mp4";	//�^�C�g������̃p�X
const string TitleScene::TITLENAME_PATH	   = "titleName.png";	//�^�C�g�����̉摜�̃p�X
const string TitleScene::TITLE_UI_PATH     = "titleUi.png";		//�v���C�V�[���֑J�ڃL�[��UI�̃p�X


/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene()
	: SceneBase(SceneType::TITLE)
	, titleMovie(0)
	, titleName(0)
	, titleUi(0)
	, alpha(0)
	, inc(0)
	, frame(0.0f)
	, selectState(SelectState::START)
{
	Initialize();
	Activate();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{
	Finalize();
}

void TitleScene::Initialize()
{
	//����f�[�^�̓ǂݍ���
	string failePath = VIDEO_FOLDER_PATH + PLAY_VIDEO_PATH;
	titleMovie = LoadGraph(failePath.c_str());

	//�^�C�g���摜UI�̓ǂݍ���
	failePath = IMAGE_FOLDER_PATH + TITLENAME_PATH;
	titleName = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + TITLE_UI_PATH;
	titleUi = LoadGraph(failePath.c_str());
}

void TitleScene::Finalize()
{
	PauseMovieToGraph(titleMovie);

	DeleteGraph(titleMovie);

	DeleteGraph(titleName);

	DeleteGraph(titleUi);
}

void TitleScene::Activate()
{
	alpha = 255;
	inc = -1;

	//�^�C�g��BGM���Đ�
	SoundManager::GetInstance().PlayBgm(SoundManager::TITLE);
}

SceneType TitleScene::Update(float deltaTime)
{
	//�f��������Đ�
	if (!GetMovieStateToGraph(titleMovie))
	{
		//���悪�I��������0�b�̏�����܂��Đ�����
		SeekMovieToGraph(titleMovie, 5000);

		//������Đ�����
		PlayMovieToGraph(titleMovie);
	}

	//�Q�[����ʂ�
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		nowSceneType = SceneType::PLAY;
	}

	return nowSceneType;
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
	//�f��������Đ�����
	DrawGraph(0, 0, titleMovie, FALSE);

	//�^�C�g�����`��
	DrawGraph(250, 450, titleName, TRUE);
	
	Blink();
}