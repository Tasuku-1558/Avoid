#pragma once

#include "DxLib.h"

/// <summary>
/// ライトクラス
/// </summary>
class Light final
{
public:

	Light(int number);
	virtual ~Light();

private:
	Light(const Light&);		//コピーコンストラクタ


	//定数
	const VECTOR TITLE_DIRECTION;	//タイトルシーンのライトの方向
	const VECTOR GAME_DIRECTION;	//ゲームシーンのライトの方向

};