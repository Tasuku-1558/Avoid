#include "Light.h"
#include "DxLib.h"


const VECTOR Light::DIRECTION = VGet(0.0f, -0.5f, 0.0f);	//ƒ‰ƒCƒg‚Ì•ûŒü

Light::Light()
{
	//ˆ—‚È‚µ
}

Light::~Light()
{
	//ˆ—‚È‚µ
}

void Light::Initialize()
{
	SetLightDirection(DIRECTION);
}