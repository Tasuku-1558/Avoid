#include "Collision.h"

namespace Math3d
{
	// ���̃R���X�g���N�^
	Sphere::Sphere()
		: localCenter()
		, worldCenter()
		, radius(0.0f)
	{
		//�����Ȃ�
	}

	// ���̃R���X�g���N�^
	Sphere::Sphere(const VECTOR& center, float radius)
		: localCenter(center)
		, worldCenter(center)
		, radius(radius)
	{
		//�����Ȃ�
	}
	
	// ���̂̃��[���h���W���ړ�����
	void Sphere::HitTestMove(const VECTOR& pos)
	{
		worldCenter = localCenter + pos;
	}
}