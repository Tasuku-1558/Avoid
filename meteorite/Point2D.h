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

	//正規化
	void Normalize();

	//長さを変える
	float Length()
	{
		return sqrt(X * X + Y * Y);
	}

	float X;
	float Y;

};

//加算
Point2D operator+(const Point2D& a, const Point2D& b);

//減算
Point2D operator-(const Point2D& a, const Point2D& b);

//スカラー積
Point2D operator*(float f, const Point2D& point);

//スカラー商
Point2D operator/(const Point2D& point, float f);