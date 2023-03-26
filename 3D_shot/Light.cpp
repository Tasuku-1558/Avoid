#include "Light.h"
#include "SceneBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Light::Light()
	: TITLE_DIRECTION({ 0.0f, 0.0f, 0.5f })
	, GAME_DIRECTION({ 0.0f, -0.5f, 0.0f })
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Light::~Light()
{
	//�����Ȃ�
}

/// <summary>
/// �^�C�g���V�[���̃��C�g�̕���
/// </summary>
void Light::TitleLight()
{
	SetLightDirection(TITLE_DIRECTION);
}

/// <summary>
/// �Q�[���V�[���̃��C�g�̕���
/// </summary>
void Light::GameLight()
{
	SetLightDirection(GAME_DIRECTION);
}