#pragma once

#include "DxLib.h"

/// <summary>
/// �I�u�W�F�N�g���N���X
/// </summary>
class ObjectBase
{
public:
	ObjectBase();
	virtual ~ObjectBase();

	virtual void Update(float deltaTime) = 0;	//�X�V����
	virtual void Draw() = 0;					//�`�揈��

	const VECTOR& GetPosition()  const { return position; }		//���W�x�N�g����Ԃ�
	const VECTOR& GetDirection() const { return direction; }	//�����x�N�g����Ԃ�

protected:

	int	   modelHandle;		//���f���n���h��
	VECTOR position;		//���W�x�N�g��
	VECTOR direction;		//�����x�N�g��
};