#include "Point2D.h"


Point2D::~Point2D()
{
	//�����Ȃ�
}

// +���Z�q
Point2D operator+(const Point2D& a, const Point2D& b)
{
	Point2D ret;
	ret.X = a.X + b.X;
	ret.Y = a.Y + b.Y;
	return ret;
}

//-���Z�q
Point2D operator-(const Point2D& a, const Point2D& b)
{
	Point2D ret;
	ret.X = a.X - b.X;
	ret.Y = a.Y - b.Y;
	return ret;
}

// �X�J���[��
Point2D operator*(float f, const Point2D& point)
{
	Point2D r;
	r.X = f * point.X;
	r.Y = f * point.Y;
	return r;
}

//�X�J���[��
Point2D operator/(const Point2D& point, float f)
{
	Point2D r;
	r.X = point.X / f;
	r.Y = point.Y / f;
	return r;
}

// ���K��
void Point2D::Normalize()
{
	float Len;
	Len = Length();

	X /= Len; Y /= Len;
}