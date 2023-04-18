#include "Light.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="lightType">ライトの種類</param>
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
/// デストラクタ
/// </summary>
Light::~Light()
{
	//処理なし
}