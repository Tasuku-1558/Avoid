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

	int lineImage;					//���胉�C���摜�i�[�p

	//�萔
	const float  LINE_CENTER_POSITION;	//���C���̒��S���W
	const float  LINE_SIZE;				//���C���̃T�C�Y
	const float  LINE_ANGLE;			//���C���̉�]�l
	const VECTOR SIZE;					//�t�B�[���h���f���̔{��
	const VECTOR POSITION;				//�t�B�[���h���f���̈ʒu
	const VECTOR ROTATE;				//�t�B�[���h���f���̉�]�l
	const VECTOR LINE_POSITION;			//���C���̈ʒu
	const string IMAGE_FOLDER_PATH;		//Image�t�H���_�܂ł̃p�X
	const string LINE_PATH;				//���C���摜�̃p�X

};