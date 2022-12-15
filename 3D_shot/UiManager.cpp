#include "UiManager.h"

using std::string;

const string UiManager::FOLDER_PATH		   = "data/image/";		//�摜�t�@�C���̃p�X
const string UiManager::UI_GRAPHIC_PATH    = "ui";				//UI�摜
const string UiManager::FILENAME_EXTENSION = ".png";			//�摜�g���q


UiManager::UiManager()
	: uiHandle()
{
	//�����Ȃ�
}

UiManager::~UiManager()
{
	//�I���������Ă΂�ĂȂ����
	if (uiHandle[0] != NULL)
	{
		Finalize();
	}
}

void UiManager::Initialize()
{
	//UI�摜�ǂݍ���
	string path = FOLDER_PATH + UI_GRAPHIC_PATH; // �t�H���_�p�X + �t�@�C����
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

void UiManager::Finalize()
{
	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		DeleteGraph(uiHandle[i]);
		uiHandle[i] = NULL;
	}
}

void UiManager::Draw(PlayScene::State state, int frame,int font, int countDown, int score, int wave)
{
	switch (state)
	{
	case PlayScene::START:
		StartGameDraw();
		break;

	case PlayScene::GAME:
		FrameDraw();
		GameUIDraw(font, countDown, score, wave);
		
		break;

	case PlayScene::FEVER:
		FrameDraw();
		GameUIDraw(font, countDown, score, wave);
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

void UiManager::FrameDraw()
{
	DrawGraph(0, -150, uiHandle[FRAME], TRUE);
}

void UiManager::FeverImageDraw()
{
	DrawRotaGraph(950, 950, 1.5f, 0, uiHandle[FEVER_IMAGE], TRUE);
}