#include "TimeSlow.h"


TimeSlow::TimeSlow()
	: slow(0.0f)
{
	//ˆ—‚È‚µ
}

TimeSlow::~TimeSlow()
{
	//ˆ—‚È‚µ
}

TimeSlow& TimeSlow::GetInstance()
{
	static TimeSlow timeSlow;
	return timeSlow;
}

void TimeSlow::SetTimeSlow(float time)
{
	slow = time;
}