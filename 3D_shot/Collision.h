#pragma once

#include "DxLib.h"
#include "Math3D.h"

namespace Math3d
{
	//���̓����蔻��
	struct Sphere
	{
		Sphere();
		Sphere(const VECTOR& center, float radius);
		void HitTestMove(const VECTOR& pos);

		VECTOR localCenter; // ���̂̃��[�J�����S���W
		VECTOR worldCenter; // ���̂̃��[���h���S���W
		float  radius;      // ���̂̔��a
	};
}