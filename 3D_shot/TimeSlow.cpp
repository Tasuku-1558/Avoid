#include "TimeSlow.h"


TimeSlow::TimeSlow()
	: slow(false)
{
	//�����Ȃ�
}

TimeSlow::~TimeSlow()
{
	//�����Ȃ�
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