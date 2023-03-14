#pragma once

#include "DxLib.h"

/// <summary>
/// ライトクラス
/// </summary>
class Light final
{
public:

	Light();
	virtual ~Light();

	void Initialize();	//初期化処理

private:

	//定数
	const VECTOR DIRECTION;	//ライトの方向

};