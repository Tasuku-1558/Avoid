#pragma once

#include "DxLib.h"

/// <summary>
/// ���C�g�N���X
/// </summary>
class Light final
{
public:

	Light();
	virtual ~Light();

	void Initialize();	//����������

private:

	//�萔
	const VECTOR DIRECTION;	//���C�g�̕���

};