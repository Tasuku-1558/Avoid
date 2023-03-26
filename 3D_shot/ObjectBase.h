#pragma once

#include "DxLib.h"

/// <summary>
/// オブジェクト基底クラス
/// </summary>
class ObjectBase
{
public:
	ObjectBase();
	virtual ~ObjectBase();

	virtual void Update(float deltaTime) = 0;				
	virtual void Draw() = 0;

	const VECTOR& GetPosition()  const { return position; }
	const VECTOR& GetDirection() const { return direction; }

protected:

	VECTOR position;		//現在の座標
	VECTOR direction;		//向きベクトル
	int	   modelHandle;		//モデルハンドル
	
};