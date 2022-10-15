#pragma once

#include "DxLib.h"
#include "math3D.h"
#include "ObjectTag.h"


class ObjectBase
{
public:
	         ObjectBase();		//�R���X�g���N�^
	virtual ~ObjectBase();		//�f�X�g���N�^

	//virtual  void Update(float dltaTime) = 0;						//= 0�͏������z�֐�
	virtual void Draw();

	const VECTOR& GetPosition() const; 	//Position��getter
	const VECTOR& GetDir() const;		//Dir��getter

protected:
	VECTOR Position;						//���݂̍��W
	VECTOR Dir;								//�����x�N�g��
	int	   ModelHandle;						//���f���n���h��
	
};