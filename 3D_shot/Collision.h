#pragma once

#include "DxLib.h"
#include "math3D.h"

namespace Math3d
{
	//球体当たり判定
	struct Sphere
	{
		Sphere();
		Sphere(const VECTOR& center, float radius);
		void HitTestMove(const VECTOR& pos);

		VECTOR LocalCenter; // 球体のローカル中心座標
		VECTOR WorldCenter; // 球体のワールド中心座標
		float  Radius;      // 球体の半径
	};

	// 当たり判定の関数組み合わせ
	//bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2);


}