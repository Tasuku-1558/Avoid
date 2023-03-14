#pragma once

#include "DxLib.h"

/// <summary>
/// カメラクラス
/// </summary>
class Camera final
{
public: 
	Camera();
	virtual ~Camera();

	void Initialize();

private:

	//定数
	static const float  NEAR_DISTANCE;		//カメラに映る手前の範囲
	static const float  FAR_DISTANCE;		//カメラに映る最奥の範囲
	static const VECTOR INITIAL_POSITION;	//初期位置
	static const VECTOR UP_VECTOR;			//カメラの上方向
};