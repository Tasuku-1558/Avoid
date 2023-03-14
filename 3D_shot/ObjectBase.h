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

	virtual void Initialize() = 0;
	virtual void Activate() = 0;
	//virtual void Update(float dltaTime) = 0;				
	virtual void Draw() = 0;

	const VECTOR& GetPosition() const; 	//position��getter
	const VECTOR& GetDir() const;		//dir��getter

protected:

	VECTOR position;						//���݂̍��W
	VECTOR dir;								//�����x�N�g��
	int	   modelHandle;						//���f���n���h��
	
};