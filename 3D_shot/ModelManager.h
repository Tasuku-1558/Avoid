#pragma once

#include <string>

using namespace std;

class ModelManager final
{
public:

	//���f���̎��
	enum ModelKind
	{
		PLAYER,
		METEORITE,
		MODEL_AMOUNT	//���f���̌�
	};

	static ModelManager& GetInstance();					  // �A�h���X��Ԃ�

	const int& GetModelHandle(ModelKind modelKind) const; // ���f���n���h���̎Q�Ƃ�Ԃ�

private:
	 ModelManager();							//�R���X�g���N�^
	~ModelManager();							//�f�X�g���N�^
	ModelManager(const ModelManager&);			//�R�s�[�R���X�g���N�^

	void LoadAllModel();						//�S�Ẵ��f���̓ǂݍ���
	void DeleteAllModel();						//�S�Ẵ��f���̍폜


	//�ÓI�萔
	static const string MODEL_FOLDER_PATH;		//model�t�H���_�܂ł̃p�X
	static const string PLAYER_PATH;			//player���f���t�@�C���̃p�X
	static const string METEORITE_PATH;			//meteorite���f���t�@�C���̃p�X

	int ModelHandle[MODEL_AMOUNT];				//���f���n���h��

};