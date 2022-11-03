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

void UiManager::Draw(PlayScene::State state, int frame , float feverGauge)
{
	switch (state)
	{
	case PlayScene::START:
		StartGameDraw();
		break;

	case PlayScene::GAME:
		FeverGaugeDraw(feverGauge);
		break;
	}
}

void UiManager::StartGameDraw()
{
	
}

void UiManager::FeverGaugeDraw(float feverGauge)
{
	DrawLine3D(VGet(-650.0f, -100.0f,0.0f), VGet(-100.0f, -100.0f, 5000.0f), GetColor(255, 0, 0));
	DrawLine3D(VGet(200.0f, 100.0f, 0.0f), VGet(250.0f, 100.0f, -700.0f), GetColor(255, 0, 0));

	float feverMaxGauge = 100.0f;
	
	DrawBox(980, 50, 980 + 850 * (feverGauge / feverMaxGauge), 110, GetColor(186, 85, 211), TRUE);
}