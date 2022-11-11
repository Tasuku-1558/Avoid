#include "TimeSlow.h"


TimeSlow::TimeSlow()
	: slow(false)
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

void TimeSlow::SetTimeSlow(bool time)
{
	slow = time;
}