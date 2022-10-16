#pragma once

#include "DxLib.h"
#include "math3D.h"

namespace Math3d
{
	//���̓����蔻��
	struct Sphere
	{
		Sphere();
		Sphere(const VECTOR& center, float radius);
		void HitTestMove(const VECTOR& pos);

		VECTOR LocalCenter; // ���̂̃��[�J�����S���W
		VECTOR WorldCenter; // ���̂̃��[���h���S���W
		float  Radius;      // ���̂̔��a
	};

	// �����蔻��̊֐��g�ݍ��킹
	//bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2);


}