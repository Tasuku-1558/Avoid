#include "Light.h"
#include "DxLib.h"


const VECTOR Light::DIRECTION = VGet(0.0f, -0.5f, 0.0f);	//���C�g�̕���

Light::Light()
{
	//�����Ȃ�
}

Light::~Light()
{
	//�����Ȃ�
}

void Light::Initialize()
{
	SetLightDirection(DIRECTION);
}