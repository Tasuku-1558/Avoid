#include "Light.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="number">���C�g�̎��</param>
Light::Light(int number)
	: TITLE_DIRECTION({ 0.0f, 0.0f, 0.5f })
	, GAME_DIRECTION({ 0.0f, -0.5f, 0.0f })
{
	if (number == 0)
	{
		SetLightDirection(TITLE_DIRECTION);
	}
	else if (number == 1)
	{
		SetLightDirection(GAME_DIRECTION);
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Light::~Light()
{
	//�����Ȃ�
}