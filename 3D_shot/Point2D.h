#pragma once

#include <math.h>

class Point2D
{
public:

	Point2D() { X = 0.0f; Y = 0.0f; }
	Point2D(float a, float b)
	{
		X = a;
		Y = b;
	}

	~Point2D();

	//���K��
	void Normalize();

	//������ς���
	float Length()
	{
		return sqrt(X * X + Y * Y);
	}

	float X;
	float Y;

};

//���Z
Point2D operator+(const Point2D& a, const Point2D& b);

//���Z
Point2D operator-(const Point2D& a, const Point2D& b);

//�X�J���[��
Point2D operator*(float f, const Point2D& point);

//�X�J���[��
Point2D operator/(const Point2D& point, float f);