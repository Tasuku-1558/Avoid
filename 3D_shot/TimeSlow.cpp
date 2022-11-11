#include "TimeSlow.h"


TimeSlow::TimeSlow()
	: slow(false)
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

void TimeSlow::SetTimeSlow(bool time)
{
	slow = time;
}