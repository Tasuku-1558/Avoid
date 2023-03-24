#pragma once

#include "ObjectBase.h"

/// <summary>
/// メテオライトベースクラス
/// </summary>
class MeteoriteBase : public ObjectBase
{
public:
	MeteoriteBase();
	virtual ~MeteoriteBase();

protected:
	
	int    random;			//ランダム値の格納用
	float  speed;			//移動速度
	bool   popFlag;			//隕石出現フラグ
	VECTOR rotate;			//回転値
	VECTOR rotateSpeed;		//回転速度


	//定数
	const int    RANGE;				//ランダム値の範囲
	const float  SPEED;				//移動速度
	const float  MAX_ROTATE;		//最大回転速度
	const float  POSITION_Z;		//Z座標
	const float  SPEED_UP;			//移動速度アップ
	const VECTOR SIZE;				//倍率
	const VECTOR DIRECTION;			//方向

};