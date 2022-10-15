#include "Collision.h"

namespace Math3d
{
	//-----------------------------------------------------------------------------
	// @brief ���̃R���X�g���N�^
	//-----------------------------------------------------------------------------
	Sphere::Sphere()
		: LocalCenter()
		, WorldCenter()
		, Radius(0.0f)
	{
	}

	//-----------------------------------------------------------------------------
	// @brief ���̃R���X�g���N�^
	//-----------------------------------------------------------------------------
	Sphere::Sphere(const VECTOR& center, float radius)
		: LocalCenter(center)
		, WorldCenter(center)
		, Radius(radius)
	{
	}

	//-----------------------------------------------------------------------------
	// @brief ���̂̃��[���h���W���ړ�����
	//-----------------------------------------------------------------------------
	void Sphere::HitTestMove(const VECTOR& pos)
	{
		WorldCenter = LocalCenter + pos;
	}

	//-----------------------------------------------------------------------------
	// @brief �����蔻�� ���E��
	// @param[in] sphere1 ��
	// @param[in] sphere2 ��
	// @return bool �����m���Ԃ����Ă���ꍇ��true ��Ԃ�
	//-----------------------------------------------------------------------------
	/*bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2)
	{
		return HitCheck_Sphere_Sphere(sphere1.WorldCenter, sphere1.Radius,
			sphere2.WorldCenter, sphere2.Radius);
	}*/

}