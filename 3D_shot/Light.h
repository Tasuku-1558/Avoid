#pragma once

#include "DxLib.h"

/// <summary>
/// ライトクラス
/// </summary>
class Light final
{
public:

	//ライトの種類
	enum class LightType
	{
		TITLE_LIGHT,	//タイトルシーンのライト
		GAME_LIGHT,		//ゲームシーンのライト
	};

	Light(LightType lightType);
	virtual ~Light();

private:
	Light(const Light&);		//コピーコンストラクタ

	//定数
	const VECTOR TITLE_DIRECTION;	//タイトルシーンのライトの方向
	const VECTOR GAME_DIRECTION;	//ゲームシーンのライトの方向
};