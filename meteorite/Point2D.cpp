#include "Point2D.h"


Point2D::~Point2D()
{
	//処理なし
}

// +演算子
Point2D operator+(const Point2D& a, const Point2D& b)
{
	Point2D ret;
	ret.X = a.X + b.X;
	ret.Y = a.Y + b.Y;
	return ret;
}

//-演算子
Point2D operator-(const Point2D& a, const Point2D& b)
{
	Point2D ret;
	ret.X = a.X - b.X;
	ret.Y = a.Y - b.Y;
	return ret;
}

// スカラー積
Point2D operator*(float f, const Point2D& point)
{
	Point2D r;
	r.X = f * point.X;
	r.Y = f * point.Y;
	return r;
}

//スカラー商
Point2D operator/(const Point2D& point, float f)
{
	Point2D r;
	r.X = point.X / f;
	r.Y = point.Y / f;
	return r;
}

// 正規化
void Point2D::Normalize()
{
	float Len;
	Len = Length();

	X /= Len; Y /= Len;
}