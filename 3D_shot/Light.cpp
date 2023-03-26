#include "Light.h"
#include "SceneBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
Light::Light()
	: TITLE_DIRECTION({ 0.0f, 0.0f, 0.5f })
	, GAME_DIRECTION({ 0.0f, -0.5f, 0.0f })
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Light::~Light()
{
	//処理なし
}

/// <summary>
/// タイトルシーンのライトの方向
/// </summary>
void Light::TitleLight()
{
	SetLightDirection(TITLE_DIRECTION);
}

/// <summary>
/// ゲームシーンのライトの方向
/// </summary>
void Light::GameLight()
{
	SetLightDirection(GAME_DIRECTION);
}