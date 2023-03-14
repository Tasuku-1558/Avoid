#include "Light.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
Light::Light()
	: DIRECTION({ 0.0f, -0.5f, 0.0f })
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
/// 初期化処理
/// </summary>
void Light::Initialize()
{
	SetLightDirection(DIRECTION);
}