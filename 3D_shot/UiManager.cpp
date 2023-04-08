#include "UiManager.h"
#include "DxLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
UiManager::UiManager()
	: uiHandle()
	, numberGraphicHandle()
	, COUNTDOWN_IMAGE_NUMBER(3)
	, IMAGE_FOLDER_PATH("Data/Image/")
	, UI_GRAPHIC_PATH("ui")
	, COUNTDOWN_GRAPHIC_PATH("CountDown")
	, IMAGE_FILENAME_EXTENSION(".png")
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
	//Ui�摜�ǂݍ���
	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		string uiPath = IMAGE_FOLDER_PATH + UI_GRAPHIC_PATH + to_string(i) + IMAGE_FILENAME_EXTENSION;
		uiHandle[i] = LoadGraph(uiPath.c_str());

		if (uiHandle[i] < 0)
		{
			printfDx("Ui�摜�ǂݍ��݂Ɏ��s[%d]\n", i);
		}
	}

	//�����摜�ǂݍ���
	string numberPath = IMAGE_FOLDER_PATH + COUNTDOWN_GRAPHIC_PATH + IMAGE_FILENAME_EXTENSION;
	LoadDivGraph(numberPath.c_str(), 3, 3, 1, 466, 467, numberGraphicHandle);

	if (numberGraphicHandle[0] < 0)
	{
		printfDx("�����摜�ǂݍ��݂Ɏ��s\n");
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
	int number = (int)frame;

	DrawGraph(720, 300, numberGraphicHandle[number], TRUE);
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