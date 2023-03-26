#pragma once

#include "ObjectBase.h"
#include <string>

using namespace std;

/// <summary>
/// �t�B�[���h�N���X
/// </summary>
class Field final : public ObjectBase
{
public:

	Field();
	virtual ~Field();

	void Draw();					//�`�揈��

private:
	Field(const Field&);			//�R�s�[�R���X�g���N�^

	void Initialize();				//����������
	void Finalize();				//�I������
	void Update(float deltaTime);	//�X�V����

	int lineHandle;					//���胉�C���i�[�p

	//�萔
	const string IMAGE_FOLDER_PATH;	//Image�t�H���_�܂ł̃p�X
	const string LINE_PATH;			//���C���摜�̃p�X
	const VECTOR SIZE;				//�{��
	const VECTOR POSITION;			//�ʒu
	const VECTOR ROTATE;			//��]�l
	const VECTOR LINE_POSITION;		//���C���̈ʒu

};