#include "UiManager.h"

using std::string;

const string UiManager::FOLLDER_PATH = "data/image/";		//�摜�t�@�C���̃p�X
const string UiManager::UI_GRAPHIC_PATH = "";


UiManager::UiManager()
	: uiHandle()
{
	//�����Ȃ�
}

UiManager::~UiManager()
{
	//�I���������Ă΂�ĂȂ����
	if (uiHandle != NULL)
	{
		Finalize();
	}
}

void UiManager::Initialize()
{
}

void UiManager::Finalize()
{
}

void UiManager::EvaluationUi(int evaluationGraph)
{
}

void UiManager::Draw(PlayScene::State state, int frame)
{
}

void UiManager::StartGameDraw()
{
}
