#include "Point2D.h"


float EaseInExponential(float start, float end, float percentage);

Point2D EaseInExponential(Point2D& start, Point2D& end, float percentage);

float EaseInExponential(float start, float end, float percentage)
{
	float diff = end - start;

	return diff * (powf(2.0f, 10.0f * (percentage - 1.0f))) + start;
}

Point2D EaseInExponential(Point2D& start, Point2D& end, float percentage)
{
	Point2D ret;
	ret.X = EaseInExponential(start.X, end.X, percentage);
	ret.Y = EaseInExponential(start.Y, end.Y, percentage);

	return ret;
}