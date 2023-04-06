#include "ModelManager.h"
#include "DxLib.h"
#include "InputManager.h"

/// <summary>
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
ModelManager::~ModelManager()
{
	DeleteAllModel();
}

/// <summary>
/// �A�h���X��Ԃ�
/// </summary>
/// <returns>modelManager��Ԃ�</returns>
ModelManager& ModelManager::GetInstance()
{
	static ModelManager modelManager;
	return modelManager;
}

/// <summary>
/// �S�Ẵ��f���̓ǂݍ���
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

		//�ǂݍ��ݎ��s�Ȃ�G���[
		if (modelHandle[i] < 0)
		{
			printfDx("���f���f�[�^�ǂݍ��ݎ��s[%d]\n", i);
		}
	}
}

/// <summary>
/// �S�Ẵ��f���̍폜
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
/// ���f���n���h���̎Q�Ƃ�Ԃ�
/// </summary>
/// <param name="modelType">���f���̎��</param>
/// <returns>���f���n���h����Ԃ�</returns>
const int& ModelManager::GetModelHandle(ModelType modelType) const
{
	if (modelType == MODEL_AMOUNT)
	{
		printfDx("�s���Ȓl���Q�Ƃ��Ă��܂�");
		return modelHandle[0];
	}

	return modelHandle[modelType];
}