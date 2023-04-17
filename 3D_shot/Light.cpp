#include "Light.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="number">ライトの種類</param>
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
/// デストラクタ
/// </summary>
Light::~Light()
{
	//処理なし
}