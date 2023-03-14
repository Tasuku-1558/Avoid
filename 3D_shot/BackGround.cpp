#include "BackGround.h"

const string BackGround::VIDEO_FOLDER_PATH		= "Data/Video/";		//Video�t�H���_�܂ł̃p�X
const string BackGround::BACK_GROUND_VIDEO_PATH = "BackGround_.mp4";	//�w�i����̃p�X


/// <summary>
/// �R���X�g���N�^
/// </summary>
BackGround::BackGround()
	: backGroundHandle(0)
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BackGround::~BackGround()
{
	Finalize();
}

void BackGround::Initialize()
{
	string failePath = VIDEO_FOLDER_PATH + BACK_GROUND_VIDEO_PATH;
	backGroundHandle = LoadGraph(failePath.c_str());
}

/// <summary>
/// �I������
/// </summary>
void BackGround::Finalize()
{
	PauseMovieToGraph(backGroundHandle);

	DeleteGraph(backGroundHandle);
}

/// <summary>
/// �X�V����
/// </summary>
void BackGround::Update()
{
	//�w�i������Đ���
	if (!GetMovieStateToGraph(backGroundHandle))
	{
		//���悪�I��������5000�b�̏�����܂��Đ�����
		SeekMovieToGraph(backGroundHandle, 5000);

		//������Đ�����
		PlayMovieToGraph(backGroundHandle);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void BackGround::Draw()
{
	//�w�i������Đ�����
	DrawGraph(0, 0, backGroundHandle, FALSE);
}