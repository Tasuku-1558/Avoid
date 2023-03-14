#pragma once

#include "DxLib.h"

/// <summary>
/// カメラクラス
/// 固定型カメラ
/// </summary>
class Camera final
{
public: 
	Camera();
	virtual ~Camera();

private:
	Camera(const Camera&);						//コピーコンストラクタ

	void Initialize();

	//定数
	static const float  NEAR_DISTANCE;		//カメラに映る手前の範囲
	static const float  FAR_DISTANCE;		//カメラに映る最奥の範囲
	static const VECTOR INITIAL_POSITION;	//初期位置
	static const VECTOR UP_VECTOR;			//カメラの上方向
};