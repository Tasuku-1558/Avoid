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
/// <returns>timeSlowを返す</returns>
TimeSlow& TimeSlow::GetInstance()
{
	static TimeSlow timeSlow;
	return timeSlow;
}

/// <summary>
/// 低速するかしないかをセットする
/// </summary>
/// <param name="slow">低速するかしないか</param>
void TimeSlow::SetTimeSlow(const bool slow)
{
	slowFlag = slow;
}