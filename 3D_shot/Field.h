#pragma once

#include "ObjectBase.h"

//�t�B�[���h�N���X
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

	VECTOR rotateAngle;

	int lineHandle;

	static const VECTOR SIZE;			//���f���̔{��
	static const VECTOR POSITION;		//���f���̈ʒu
	static const VECTOR ROTATE;			//���f���̉�]

};