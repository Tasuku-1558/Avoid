#include "MeteoriteBase.h"

const float MeteoriteBase::SIZE					  = 0.3f;		//モデル倍率
const float MeteoriteBase::SPEED				  = 600.0f;		//移動速度
const int	MeteoriteBase::RANDOM_RANGE_X_OR_Y	  = 450;		//X座標とY座標のランダム座標
const float MeteoriteBase::Z_POSITION			  = 1600.0f;	//Z座標
const int   MeteoriteBase::RANDOM_ROTATION_SPEED  = 80;			//ランダムな回転スピード
const float MeteoriteBase::RADIUS				  = 65.0f;		//半径の範囲
const int   MeteoriteBase::METEORITE_ARRAY_NUMBER = 10;			//隕石の配列数


MeteoriteBase::MeteoriteBase(ObjectTag tag)
	: Tag(tag)
	, RotateSpeed()
	, RotateAngle()
	/*, PopCount(0.0f)*/
	, PopFlag(true)
{
	//処理なし
}

MeteoriteBase::~MeteoriteBase()
{
	//処理なし
}