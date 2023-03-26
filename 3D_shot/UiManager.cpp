#include "UiManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
UiManager::UiManager()
	: uiHandle()
	, fever(false)
	, FOLDER_PATH("Data/image/")
	, UI_GRAPHIC_PATH("ui")
	, FILENAME_EXTENSION(".png")
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
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="gameState"></param>
/// <param name="font"></param>
/// <param name="countDown"></param>
/// <param name="score"></param>
/// <param name="wave"></param>
void UiManager::Draw(GameScene::GameState gameState, int font, int countDown, int score, int wave)
{
	switch (gameState)
	{
	case GameScene::GameState::START:
		StartGameDraw();
		break;

	case GameScene::GameState::GAME:
		FrameDraw();
		GameUIDraw(font, countDown, score, wave);
		
		break;

	case GameScene::GameState::FINALWAVE:
		FrameDraw();
		GameUIDraw(font, countDown, score, wave);
		fever = true;
		FeverImageDraw();
		break;
	}
}

void UiManager::StartGameDraw()
{
	
}

void UiManager::GameUIDraw(int font, int countDown, int score, int wave)
{
	//�������ԕ\��
	DrawFormatStringToHandle(500, 100, GetColor(255, 0, 0), font, "TIME : %d", countDown);

	//�l���X�R�A�\��
	DrawFormatStringToHandle(1000, 100, GetColor(255, 255, 0), font, "SCORE : %d", score);

	//覐΂̃E�F�[�u�\��
	DrawFormatStringToHandle(100, 100, GetColor(0, 255, 0), font, "WAVE : %d", wave);
}

/// <summary>
/// �������ԂƃX�R�A�̘g�`�揈��
/// </summary>
void UiManager::FrameDraw()
{
	DrawGraph(0, -150, uiHandle[FRAME], TRUE);
}

/// <summary>
/// �t�B�[�o�[���[�hUI�̕`��
/// </summary>
void UiManager::FeverImageDraw()
{
	if (fever)
	{
		DrawRotaGraph(950, 950, 1.5f, 0, uiHandle[FEVER_IMAGE], TRUE);
	}
}