#include "ModelManager.h"
#include "DxLib.h"


const string ModelManager::MODEL_FOLDER_PATH = "data/model/";	//modelフォルダまでのパス
const string ModelManager::PLAYER_PATH		 = "player.mv1";	//playerモデルファイルのパス
const string ModelManager::LING_PATH		 = "ling.mv1";		//lingモデルファイルのパス
const string ModelManager::METEORITE_PATH	 = "meteorite.mv1"; //meteoriteモデルファイルのパス
const string ModelManager::FIELD_PATH		 = "field.mv1";		//fieldモデルファイルのパス


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
	//モデルファイルへのパス
	string failePath = MODEL_FOLDER_PATH + PLAYER_PATH;
	modelHandle[PLAYER] = MV1LoadModel(failePath.c_str());

	failePath = MODEL_FOLDER_PATH + LING_PATH;
	modelHandle[PLAYER_LING] = MV1LoadModel(failePath.c_str());

	failePath = MODEL_FOLDER_PATH + METEORITE_PATH;
	modelHandle[METEORITE] = MV1LoadModel(failePath.c_str());

	failePath = MODEL_FOLDER_PATH + FIELD_PATH;
	modelHandle[FIELD] = MV1LoadModel(failePath.c_str());

	//読み込み失敗ならエラー
	for (int i = 0; i < MODEL_AMOUNT; ++i)
	{
		if (modelHandle[i] < 0)
		{
			printfDx("モデルデータ読み込み失敗\n", i);
		}
	}
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
		printfDx("不正な値を参照しています");
		return modelHandle[0];
	}

	return modelHandle[modelType];
}