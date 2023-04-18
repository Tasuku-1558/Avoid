#include "Light.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="lightType">���C�g�̎��</param>
Light::Light(LightType lightType)
	: TITLE_DIRECTION({ 0.0f, 0.0f, 0.5f })
	, GAME_DIRECTION({ 0.0f, -0.5f, 0.0f })
{
	if (lightType == LightType::TITLE_LIGHT)
	{
		SetLightDirection(TITLE_DIRECTION);
	}

	if (lightType == LightType::GAME_LIGHT)
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