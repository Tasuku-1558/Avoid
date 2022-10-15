#include "ModelManager.h"
#include "DxLib.h"


const string ModelManager::MODEL_FOLDER_PATH = "Data/model/";	//model�t�H���_�܂ł̃p�X
const string ModelManager::PLAYER_PATH		 = "player.mv1";	//player���f���t�@�C���̃p�X
const string ModelManager::METEORITE_PATH	 = "meteorite.mv1"; //meteorite���f���t�@�C���̃p�X


ModelManager::ModelManager()
	: ModelHandle()
{
	LoadAllModel();
}

ModelManager::~ModelManager()
{
	DeleteAllModel();
}

ModelManager& ModelManager::GetInstance()
{
	static ModelManager ModelManager;
	return ModelManager;
}

void ModelManager::LoadAllModel()
{
	//���f���t�@�C���ւ̃p�X
	string FailePath = MODEL_FOLDER_PATH + PLAYER_PATH;
	ModelHandle[PLAYER] = MV1LoadModel(FailePath.c_str());

	FailePath = MODEL_FOLDER_PATH + METEORITE_PATH;
	ModelHandle[METEORITE] = MV1LoadModel(FailePath.c_str());

	//�ǂݍ��ݎ��s�Ȃ�G���[
	for (int i = 0; i < MODEL_AMOUNT; ++i)
	{
		if (ModelHandle[i] < 0)
		{
			printfDx("���f���f�[�^�ǂݍ��ݎ��s\n", i);
		}
	}
}

void ModelManager::DeleteAllModel()
{
	for (int i = 0; i < MODEL_AMOUNT; ++i)
	{
		if (ModelHandle[i] != NULL)
		{
			MV1DeleteModel(ModelHandle[i]);
			ModelHandle[i] = NULL;
		}
	}
}

const int& ModelManager::GetModelHandle(ModelKind modelKind) const
{
	if (modelKind == MODEL_AMOUNT)
	{
		printfDx("�s���Ȓl���Q�Ƃ��Ă��܂�");
		return ModelHandle[0];
	}

	return ModelHandle[modelKind];
}