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

	virtual void Update(float deltaTime) = 0;				
	virtual void Draw() = 0;

	const VECTOR& GetPosition()  const { return position; }
	const VECTOR& GetDirection() const { return direction; }

protected:

	int	   modelHandle;		//���f���n���h��
	VECTOR position;		//���݂̍��W
	VECTOR direction;		//�����x�N�g��
	
};