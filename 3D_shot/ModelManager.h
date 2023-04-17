#pragma once

#include <string>

using namespace std;

/// <summary>
/// �V���O���g��
/// ���f���Ǘ��N���X
/// </summary>
class ModelManager final
{
public:
	
	//���f���̎��
	enum ModelType
	{
		PLAYER,			//�v���C���[���f��
		PLAYER_LING,	//�v���C���[�̃����O���f��
		METEORITE,		//覐΃��f��
		FIELD,			//�X�e�[�W���f��
		MODEL_AMOUNT,	//���f���̐�
	};

	static ModelManager& GetInstance();					  //�A�h���X��Ԃ�

	const int& GetModelHandle(ModelType modelType) const; //���f���n���h���̎Q�Ƃ�Ԃ�

private:
	ModelManager();
	ModelManager(const ModelManager&);	//�R�s�[�R���X�g���N�^
	virtual ~ModelManager();

	void LoadAllModel();	//�S�Ẵ��f���̓ǂݍ���
	void DeleteAllModel();	//�S�Ẵ��f���̍폜

	struct Model
	{
		string modelPath;	//���f���̃p�X
	};

	int modelHandle[MODEL_AMOUNT];	//���f���n���h���i�[�p

	//�萔
	const string MODEL_FOLDER_PATH;		//Model�t�H���_�܂ł̃p�X
	const string PLAYER_PATH;			//player���f���t�@�C���̃p�X
	const string LING_PATH;				//ling���f���t�@�C���̃p�X
	const string METEORITE_PATH;		//meteorite���f���t�@�C���̃p�X
	const string FIELD_PATH;			//field���f���t�@�C���̃p�X

};