#pragma once

#include "ObjectBase.h"

/// <summary>
/// 隕石基底クラス
/// </summary>
class MeteoriteBase : public ObjectBase
{
public:
	MeteoriteBase();
	virtual ~MeteoriteBase();

protected:
	
	int    randomDirection;	//隕石が進む方向のランダム値の格納用
	float  speed;			//移動速度
	bool   popFlag;			//隕石出現フラグ
	VECTOR playerPosition;	//プレイヤーの位置
	VECTOR rotate;			//回転値
	VECTOR rotateSpeed;		//回転速度


	//定数
	const int    RANGE_DIRECTION;	//隕石が進む方向のランダム値の範囲
	const float  SPEED;				//移動速度
	const float  MAX_ROTATE;		//最大回転速度
	const float  SPEED_UP;			//移動速度アップ
	const VECTOR RANDOM_POSITION;	//ランダムな出現位置
	const VECTOR SIZE;				//倍率
	const VECTOR DIRECTION;			//方向

};