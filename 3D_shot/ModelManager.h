#pragma once

#include <string>

using namespace std;


/// <summary>
/// ���f���Ǘ��N���X
/// </summary>
class ModelManager final
{
public:

	/// <summary>
	/// ���f���̎��
	/// </summary>
	enum ModelType
	{
		PLAYER,
		PLAYER_LING,
		METEORITE,
		FIELD,
		MODEL_AMOUNT	//���f���̌�
	};

	static ModelManager& GetInstance();					  // �A�h���X��Ԃ�

	const int& GetModelHandle(ModelType modelType) const; // ���f���n���h���̎Q�Ƃ�Ԃ�

private:
	 ModelManager();							//�R���X�g���N�^
	~ModelManager();							//�f�X�g���N�^

	 ModelManager(const ModelManager&);			//�R�s�[�R���X�g���N�^

	void LoadAllModel();						//�S�Ẵ��f���̓ǂݍ���
	void DeleteAllModel();						//�S�Ẵ��f���̍폜


	int modelHandle[MODEL_AMOUNT];				//���f���n���h���i�[�p

	//�ÓI�萔
	static const string MODEL_FOLDER_PATH;		//model�t�H���_�܂ł̃p�X
	static const string PLAYER_PATH;			//player���f���t�@�C���̃p�X
	static const string LING_PATH;				//ling���f���t�@�C���̃p�X
	static const string METEORITE_PATH;			//meteorite���f���t�@�C���̃p�X
	static const string FIELD_PATH;				//field���f���t�@�C���̃p�X

};