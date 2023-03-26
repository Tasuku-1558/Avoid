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

	void TitleLight();			//タイトルシーン用ライト
	void GameLight();			//ゲームシーン用ライト

private:
	Light(const Light&);		//コピーコンストラクタ


	//定数
	const VECTOR TITLE_DIRECTION;	//タイトルシーンのライトの方向
	const VECTOR GAME_DIRECTION;	//ゲームシーンのライトの方向

};