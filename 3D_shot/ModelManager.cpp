#include "ModelManager.h"
#include "DxLib.h"
#include "InputManager.h"

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
/// <returns>modelManagerを返す</returns>
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
	Model model[] =
	{
		{PLAYER_PATH},
		{LING_PATH},
		{METEORITE_PATH},
		{FIELD_PATH},
	};

	for (int i = 0; i < MODEL_AMOUNT; ++i)
	{
		modelHandle[i] = MV1LoadModel(Input::InputPath(MODEL_FOLDER_PATH, model[i].modelPath).c_str());

		//読み込み失敗ならエラー
		if (modelHandle[i] < 0)
		{
			printfDx("モデルデータ読み込み失敗[%d]\n", i);
		}
	}
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
/// <param name="modelType">モデルの種類</param>
/// <returns>モデルハンドルを返す</returns>
const int& ModelManager::GetModelHandle(ModelType modelType) const
{
	if (modelType == MODEL_AMOUNT)
	{
		printfDx("不正な値を参照しています");
		return modelHandle[0];
	}

	return modelHandle[modelType];
}