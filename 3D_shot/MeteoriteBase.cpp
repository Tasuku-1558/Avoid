#include "MeteoriteBase.h"


const VECTOR MeteoriteBase::SIZE				   = VGet(0.3f, 0.3f, 0.3f);	//モデル倍率
const float  MeteoriteBase::SPEED				   = 1500.0f;					//移動速度
const int	 MeteoriteBase::RANDOM_RANGE_X_OR_Y    = 400;						//X座標とY座標のランダム座標
const float  MeteoriteBase::Z_POSITION			   = 1600.0f;					//Z座標
const VECTOR MeteoriteBase::DIR					   = VGet(0.0f, 0.0f, -1.0f);	//方向
const int    MeteoriteBase::RANDOM_ROTATION_SPEED  = 400;						//ランダムな回転スピード
const float  MeteoriteBase::RADIUS				   = 65.0f;						//半径の範囲
const int	 MeteoriteBase::RANGE				   = 2;							//ランダム値の範囲


MeteoriteBase::MeteoriteBase()
	: rotateSpeed()
	, rotateAngle()
	, popFlag(true)
	, random(0)
	, speed(0.0f)
{
	//処理なし
}

MeteoriteBase::~MeteoriteBase()
{
	//処理なし
}