#include "TimeSlow.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
TimeSlow::TimeSlow()
	: slowFlag(false)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TimeSlow::~TimeSlow()
{
	//�����Ȃ�
}

/// <summary>
/// �A�h���X��Ԃ�
/// </summary>
/// <returns>timeSlow��Ԃ�</returns>
TimeSlow& TimeSlow::GetInstance()
{
	static TimeSlow timeSlow;
	return timeSlow;
}

void TimeSlow::SetTimeSlow(const bool slow)
{
	slowFlag = slow;
}