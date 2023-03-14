#include "ModelManager.h"
#include "DxLib.h"


const string ModelManager::MODEL_FOLDER_PATH = "data/model/";	//model�t�H���_�܂ł̃p�X
const string ModelManager::PLAYER_PATH		 = "player.mv1";	//player���f���t�@�C���̃p�X
const string ModelManager::LING_PATH		 = "ling.mv1";		//ling���f���t�@�C���̃p�X
const string ModelManager::METEORITE_PATH	 = "meteorite.mv1"; //meteorite���f���t�@�C���̃p�X
const string ModelManager::FIELD_PATH		 = "field.mv1";		//field���f���t�@�C���̃p�X


ModelManager::ModelManager()
	: modelHandle()
{
	LoadAllModel();
}

ModelManager::~ModelManager()
{
	DeleteAllModel();
}

ModelManager& ModelManager::GetInstance()
{
	static ModelManager modelManager;
	return modelManager;
}

void ModelManager::LoadAllModel()
{
	//���f���t�@�C���ւ̃p�X
	modelHandle[PLAYER]		 = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, PLAYER_PATH).c_str());

	modelHandle[PLAYER_LING] = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, LING_PATH).c_str());

	modelHandle[METEORITE]	 = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, METEORITE_PATH).c_str());

	modelHandle[FIELD]		 = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, FIELD_PATH).c_str());

	//�ǂݍ��ݎ��s�Ȃ�G���[
	for (int i = 0; i < MODEL_AMOUNT; ++i)
	{
		if (modelHandle[i] < 0)
		{
			printfDx("���f���f�[�^�ǂݍ��ݎ��s\n", i);
		}
	}
}

/// <summary>
/// ���f���̃p�X�����
/// </summary>
/// <param name="folderPath"></param>
/// <param name="path"></param>
/// <returns></returns>
string ModelManager::InputPath(string folderPath, string path)
{
	return string(folderPath + path);
}

void ModelManager::DeleteAllModel()
{
	for (int i = 0; i < MODEL_AMOUNT; ++i)
	{
		if (modelHandle[i] != NULL)
		{
			MV1DeleteModel(modelHandle[i]);
			modelHandle[i] = NULL;
		}
	}
}

const int& ModelManager::GetModelHandle(ModelType modelType) const
{
	if (modelType == MODEL_AMOUNT)
	{
		printfDx("�s���Ȓl���Q�Ƃ��Ă��܂�");
		return modelHandle[0];
	}

	return modelHandle[modelType];
}