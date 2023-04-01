#include "UiManager.h"
#include "DxLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
UiManager::UiManager()
	: uiHandle()
	, numberGraphicHandle()
	, FOLDER_PATH("Data/Image/")
	, UI_GRAPHIC_PATH("ui")
	, COUNTDOWN_GRAPHIC_PATH("CountDown")
	, FILENAME_EXTENSION(".png")
	, COUNTDOWN_IMAGE_NUMBER(3)
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UiManager::~UiManager()
{
	//�I���������Ă΂�ĂȂ����
	if (uiHandle[0] != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// ����������
/// </summary>
void UiManager::Initialize()
{
	//UI�摜�ǂݍ���
	string path = FOLDER_PATH + UI_GRAPHIC_PATH;	//�t�H���_�p�X + �t�@�C����
	string fullPath = path;
	
	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		fullPath = path + std::to_string(i) + FILENAME_EXTENSION;
		uiHandle[i] = LoadGraph(fullPath.c_str());

		if (uiHandle[i] < 0)
		{
			printfDx("�摜�ǂݍ��݂Ɏ��s[%d]\n", i);
		}
	}

	//�����摜�ǂݍ���
	fullPath = FOLDER_PATH + COUNTDOWN_GRAPHIC_PATH + FILENAME_EXTENSION;
	LoadDivGraph(fullPath.c_str(), 3, 3, 1, 383, 450, numberGraphicHandle);

	if (numberGraphicHandle[0] < 0)
	{
		printfDx("�摜�ǂݍ��݂Ɏ��s_UiManager_number\n");
	}
}

/// <summary>
/// �I������
/// </summary>
void UiManager::Finalize()
{
	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		DeleteGraph(uiHandle[i]);
		uiHandle[i] = NULL;
	}

	for (int i = 0; i < COUNTDOWN_IMAGE_NUMBER; ++i)
	{
		DeleteGraph(numberGraphicHandle[i]);
		numberGraphicHandle[i] = NULL;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="gameState">�Q�[���̏��</param>
/// <param name="frame">�t���[����</param>
/// <param name="font">�Q�[���t�H���g</param>
/// <param name="countDown">�Q�[��������</param>
/// <param name="score">�l���X�R�A</param>
/// <param name="wave">�E�F�[�u</param>
void UiManager::Draw(GameScene::GameState gameState, float frame, int font, int countDown, int score, int wave)
{
	switch (gameState)
	{
	case GameScene::GameState::START:
		StartCountDraw(frame);
		break;

	case GameScene::GameState::GAME:
		FrameDraw();
		GameUiDraw(font, countDown, score, wave);
		break;
	}
}

/// <summary>
/// �J�E���g�_�E���`��
/// </summary>
/// <param name="frame">�t���[����</param>
void UiManager::StartCountDraw(float frame)
{
	int num = (int)frame;

	DrawGraph(800, 350, numberGraphicHandle[num], TRUE);
}

/// <summary>
/// �Q�[����UI�`��
/// </summary>
/// <param name="font">�Q�[���t�H���g</param>
/// <param name="countDown">�Q�[��������</param>
/// <param name="score">�l���X�R�A</param>
/// <param name="wave">�E�F�[�u</param>
void UiManager::GameUiDraw(int font, int countDown, int score, int wave)
{
	//�������ԕ\��
	DrawFormatStringToHandle(500, 100, GetColor(255, 0, 0), font, "TIME : %d", countDown);

	//�l���X�R�A�\��
	DrawFormatStringToHandle(1000, 100, GetColor(255, 255, 0), font, "SCORE : %d", score);

	//覐΂̃E�F�[�u�\��
	DrawFormatStringToHandle(100, 100, GetColor(0, 255, 0), font, "WAVE : %d", wave);
}

/// <summary>
/// �g�`��
/// </summary>
void UiManager::FrameDraw()
{
	DrawGraph(0, -150, uiHandle[FRAME], TRUE);
}