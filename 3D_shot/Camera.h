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
	Camera(const Camera&);			//コピーコンストラクタ

	void Initialize();				//初期化処理

	//定数
	const float  NEAR_DISTANCE;		//カメラに映る手前の範囲
	const float  FAR_DISTANCE;		//カメラに映る最奥の範囲
	const VECTOR INITIAL_POSITION;	//初期位置
	const VECTOR UP_VECTOR;			//カメラの上方向
};