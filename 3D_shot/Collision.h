#pragma once

#include "DxLib.h"
#include "Math3D.h"

namespace Math3d
{
	//球体当たり判定
	struct Sphere
	{
		Sphere();
		Sphere(const VECTOR& center, float radius);
		void HitTestMove(const VECTOR& pos);

		VECTOR localCenter; // 球体のローカル中心座標
		VECTOR worldCenter; // 球体のワールド中心座標
		float  radius;      // 球体の半径
	};
}