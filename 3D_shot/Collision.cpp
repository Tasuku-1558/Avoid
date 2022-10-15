#include "Collision.h"

namespace Math3d
{
	//-----------------------------------------------------------------------------
	// @brief 球体コンストラクタ
	//-----------------------------------------------------------------------------
	Sphere::Sphere()
		: LocalCenter()
		, WorldCenter()
		, Radius(0.0f)
	{
	}

	//-----------------------------------------------------------------------------
	// @brief 球体コンストラクタ
	//-----------------------------------------------------------------------------
	Sphere::Sphere(const VECTOR& center, float radius)
		: LocalCenter(center)
		, WorldCenter(center)
		, Radius(radius)
	{
	}

	//-----------------------------------------------------------------------------
	// @brief 球体のワールド座標を移動する
	//-----------------------------------------------------------------------------
	void Sphere::HitTestMove(const VECTOR& pos)
	{
		WorldCenter = LocalCenter + pos;
	}

	//-----------------------------------------------------------------------------
	// @brief 当たり判定 球・球
	// @param[in] sphere1 球
	// @param[in] sphere2 球
	// @return bool 球同士がぶつかっている場合はtrue を返す
	//-----------------------------------------------------------------------------
	/*bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2)
	{
		return HitCheck_Sphere_Sphere(sphere1.WorldCenter, sphere1.Radius,
			sphere2.WorldCenter, sphere2.Radius);
	}*/

}