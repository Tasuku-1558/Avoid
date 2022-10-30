#include "Collision.h"

namespace Math3d
{
	// 球体コンストラクタ
	Sphere::Sphere()
		: localCenter()
		, worldCenter()
		, radius(0.0f)
	{
		//処理なし
	}

	// 球体コンストラクタ
	Sphere::Sphere(const VECTOR& center, float radius)
		: localCenter(center)
		, worldCenter(center)
		, radius(radius)
	{
		//処理なし
	}
	
	// 球体のワールド座標を移動する
	void Sphere::HitTestMove(const VECTOR& pos)
	{
		worldCenter = localCenter + pos;
	}
}