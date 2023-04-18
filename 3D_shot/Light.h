#pragma once

#include "DxLib.h"

/// <summary>
/// ���C�g�N���X
/// </summary>
class Light final
{
public:

	//���C�g�̎��
	enum class LightType
	{
		TITLE_LIGHT,	//�^�C�g���V�[���̃��C�g
		GAME_LIGHT,		//�Q�[���V�[���̃��C�g
	};

	Light(LightType lightType);
	virtual ~Light();

private:
	Light(const Light&);		//�R�s�[�R���X�g���N�^


	//�萔
	const VECTOR TITLE_DIRECTION;	//�^�C�g���V�[���̃��C�g�̕���
	const VECTOR GAME_DIRECTION;	//�Q�[���V�[���̃��C�g�̕���

};