#include "ModelManager.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
ModelManager::ModelManager()
	: modelHandle()
	, MODEL_FOLDER_PATH("Data/Model/")
	, PLAYER_PATH("Player/player.mv1")
	, LING_PATH("Player/ling.mv1")
	, METEORITE_PATH("Meteorite/meteorite.mv1")
	, FIELD_PATH("Field/field.mv1")
{
	LoadAllModel();
}

/// <summary>
/// デストラクタ
/// </summary>
ModelManager::~ModelManager()
{
	DeleteAllModel();
}

/// <summary>
/// アドレスを返す
/// </summary>
/// <returns></returns>
ModelManager& ModelManager::GetInstance()
{
	static ModelManager modelManager;
	return modelManager;
}

/// <summary>
/// 全てのモデルの読み込み
/// </summary>
void ModelManager::LoadAllModel()
{
	modelHandle[PLAYER]		 = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, PLAYER_PATH).c_str());

	modelHandle[PLAYER_LING] = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, LING_PATH).c_str());

	modelHandle[METEORITE]	 = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, METEORITE_PATH).c_str());

	modelHandle[FIELD]		 = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, FIELD_PATH).c_str());

	//読み込み失敗ならエラー
	for (int i = 0; i < MODEL_AMOUNT; ++i)
	{
		if (modelHandle[i] < 0)
		{
			printfDx("モデルデータ読み込み失敗[%d]\n", i);
		}
	}
}

/// <summary>
/// モデルのパスを入力
/// </summary>
/// <param name="folderPath">モデルフォルダのパス</param>
/// <param name="modelPath">モデルのパス</param>
/// <returns></returns>
string ModelManager::InputPath(string folderPath, string modelPath)
{
	return string(folderPath + modelPath);
}

/// <summary>
/// 全てのモデルの削除
/// </summary>
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

/// <summary>
/// モデルハンドルの参照を返す
/// </summary>
/// <param name="modelType"></param>
/// <returns></returns>
const int& ModelManager::GetModelHandle(ModelType modelType) const
{
	if (modelType == MODEL_AMOUNT)
	{
		printfDx("不正な値を参照しています");
		return modelHandle[0];
	}

	return modelHandle[modelType];
}