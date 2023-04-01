#include "TimeSlow.h"


/// <summary>
/// コンストラクタ
/// </summary>
TimeSlow::TimeSlow()
	: slowFlag(false)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
TimeSlow::~TimeSlow()
{
	//処理なし
}

/// <summary>
/// アドレスを返す
/// </summary>
/// <returns></returns>
TimeSlow& TimeSlow::GetInstance()
{
	static TimeSlow timeSlow;
	return timeSlow;
}

void TimeSlow::SetTimeSlow(const bool slow)
{
	slowFlag = slow;
}