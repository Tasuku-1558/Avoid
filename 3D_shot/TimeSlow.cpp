#include "TimeSlow.h"


TimeSlow::TimeSlow()
	: slow(0.0f)
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

void TimeSlow::SetTimeSlow(float time)
{
	slow = time;
}