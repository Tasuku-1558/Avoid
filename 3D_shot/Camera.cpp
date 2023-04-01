#include "Camera.h"


/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
	: NEAR_DISTANCE(1.0f)
	, FAR_DISTANCE(3000.0f)
	, INITIAL_POSITION({ 0.0f, 200.0f, -550.0f })
	, UP_VECTOR({ 0.0f, 200.0f, 0.0f })
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void Camera::Initialize()
{
	//カメラの手前と奥の距離を設定
	SetCameraNearFar(NEAR_DISTANCE, FAR_DISTANCE);

	//カメラの視点とターゲットを見る角度にカメラを設置
	SetCameraPositionAndTarget_UpVecY(INITIAL_POSITION, UP_VECTOR);
}