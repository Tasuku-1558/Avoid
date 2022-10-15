#include "ModelManager.h"
#include "DxLib.h"


const string ModelManager::MODEL_FOLDER_PATH = "Data/model/";	//modelフォルダまでのパス
const string ModelManager::PLAYER_PATH		 = "player.mv1";	//playerモデルファイルのパス
const string ModelManager::METEORITE_PATH	 = "meteorite.mv1"; //meteoriteモデルファイルのパス


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
	//モデルファイルへのパス
	string FailePath = MODEL_FOLDER_PATH + PLAYER_PATH;
	ModelHandle[PLAYER] = MV1LoadModel(FailePath.c_str());

	FailePath = MODEL_FOLDER_PATH + METEORITE_PATH;
	ModelHandle[METEORITE] = MV1LoadModel(FailePath.c_str());

	//読み込み失敗ならエラー
	for (int i = 0; i < MODEL_AMOUNT; ++i)
	{
		if (ModelHandle[i] < 0)
		{
			printfDx("モデルデータ読み込み失敗\n", i);
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
		printfDx("不正な値を参照しています");
		return ModelHandle[0];
	}

	return ModelHandle[modelKind];
}