#include "MeteoriteBase.h"


/// <summary>
/// コンストラクタ
/// </summary>
MeteoriteBase::MeteoriteBase()
	: random(0)
	, speed(0.0f)
	, popFlag(true)
	, rotate()
	, rotateSpeed()
	, RANGE(2)
	, SPEED(1500.0f)
	, MAX_ROTATE(0.2f)
	, POSITION_Z(1600.0f)
	, SPEED_UP(2500.0f)
	, SIZE({ 0.3f, 0.3f, 0.3f })
	, DIRECTION({ 0.0f, 0.0f, -1.0f })
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
MeteoriteBase::~MeteoriteBase()
{
	//処理なし
}