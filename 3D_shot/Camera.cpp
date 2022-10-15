#include "Camera.h"

const float  Camera::NEAR_DISTANCE	  = 1.0f;						//カメラに映る手前の範囲
const float  Camera::FAR_DISTANCE	  = 2000.0f;					//カメラに映る最奥の範囲
const VECTOR Camera::INITIAL_POSITION = { 0.0f, 200.0f, -550.0f };	//初期位置
const VECTOR Camera::UP_VECTOR		  = { 0.0f, 200.0f, 0.0f };		//カメラの上方向

Camera::Camera()
{
	//処理なし
}

Camera::~Camera()
{
	//処理なし
}

void Camera::Update()
{
	//奥行0.1～1000までをカメラの描画範囲とする
	//カメラの手前と奥の距離を設定する
	SetCameraNearFar(NEAR_DISTANCE, FAR_DISTANCE);

	//カメラ(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
	SetCameraPositionAndTarget_UpVecY(INITIAL_POSITION, UP_VECTOR);
}
