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

	void Draw();

private:
	Field(const Field&);		//�R�s�[�R���X�g���N�^

	void Initialize();
	void Finalize();

	VECTOR rotate;				//��]�l�i�[�p
	int lineHandle;				//���胉�C���i�[�p

	//�ÓI�萔
	static const string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	static const string LINE_PATH;			//���C���摜�̃p�X
	static const VECTOR SIZE;				//���f���̔{��
	static const VECTOR POSITION;			//���f���̈ʒu
	static const VECTOR ROTATE;				//���f���̉�]

};