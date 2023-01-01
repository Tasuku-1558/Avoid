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
	~Field();

	void Initialize();
	void Finalize();
	void Activate();
	void Draw();

private:

	VECTOR rotateAngle;					//��]�l�i�[�p
	int lineHandle;						//���胉�C���i�[�p

	//�ÓI�萔
	static const VECTOR SIZE;			//���f���̔{��
	static const VECTOR POSITION;		//���f���̈ʒu
	static const VECTOR ROTATE;			//���f���̉�]
	static const string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	static const string LINE_PATH;			//���C���摜�̃p�X

};