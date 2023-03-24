#include "TitleScene.h"
#include "DxLib.h"
#include "SoundManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene()
	: SceneBase(SceneType::TITLE)
	, selectState(SelectState::START)
	, titleMovie(0)
	, titleName(0)
	, titleUi(0)
	, alpha(255)
	, inc(-1)
	, frame(0.0f)
	, VIDEO_FOLDER_PATH("Data/Video/")
	, IMAGE_FOLDER_PATH("Data/image/")
	, PLAY_VIDEO_PATH("PlayVideo.mp4")
	, TITLENAME_PATH("titleName.png")
	, TITLE_UI_PATH("titleUi.png")
	, MAX_ALPHA(255)
	, PLAY_POSITION(5000)
{
	Initialize();
	Activate();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{
	PauseMovieToGraph(titleMovie);

	DeleteGraph(titleMovie);

	DeleteGraph(titleName);

	DeleteGraph(titleUi);
}

/// <summary>
/// ����������
/// </summary>
void TitleScene::Initialize()
{
	//����f�[�^�̓ǂݍ���
	titleMovie = LoadGraph(InputPath(VIDEO_FOLDER_PATH, PLAY_VIDEO_PATH).c_str());

	//�^�C�g���摜UI�̓ǂݍ���
	titleName = LoadGraph(InputPath(IMAGE_FOLDER_PATH, TITLENAME_PATH).c_str());

	titleUi = LoadGraph(InputPath(IMAGE_FOLDER_PATH, TITLE_UI_PATH).c_str());
}

/// <summary>
/// �p�X�����
/// </summary>
/// <param name="folderPath">�t�H���_�܂ł̃p�X</param>
/// <param name="path"></param>
/// <returns></returns>
string TitleScene::InputPath(string folderPath, string path)
{
	return string(folderPath + path);
}

/// <summary>
/// ����������
/// </summary>
void TitleScene::Activate()
{
	//�^�C�g��BGM���Đ�
	SoundManager::GetInstance().PlayBgm(SoundManager::TITLE);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <returns></returns>
SceneType TitleScene::Update(float deltaTime)
{
	//�f��������Đ�
	if (!GetMovieStateToGraph(titleMovie))
	{
		//���悪�I��������5000�b�̏�����܂��Đ�����
		SeekMovieToGraph(titleMovie, PLAY_POSITION);

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
	if (alpha > MAX_ALPHA && inc > 0)
	{
		inc *= -1;
	}

	if (alpha < 0 && inc < 0)
	{
		inc *= -1;
	}

	alpha += inc;
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	
	DrawGraph(400, 700, titleUi, TRUE);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

/// <summary>
/// �`�揈��
/// </summary>
void TitleScene::Draw()
{
	//�f��������Đ�����
	DrawGraph(0, 0, titleMovie, FALSE);

	//�^�C�g�����`��
	DrawGraph(250, 450, titleName, TRUE);
	
	Blink();
}