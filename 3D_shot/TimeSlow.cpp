#include "TimeSlow.h"


TimeSlow::TimeSlow()
	: slow(0.0f)
{
	//処理なし
}

TimeSlow::~TimeSlow()
{
	//処理なし
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