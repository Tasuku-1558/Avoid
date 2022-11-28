#pragma once

#include "ObjectBase.h"

//Meteoriteの親クラス
//ObjectBaseを継承


class MeteoriteBase : public ObjectBase
{
public:
			 MeteoriteBase();
	virtual ~MeteoriteBase();

	static const int METEORITE_ARRAY_NUMBER;	//隕石の配列数

protected:
	
	VECTOR rotateSpeed;							//回転速度 x,y,z
	VECTOR rotateAngle;							//回転角 x,y,z
	bool   popFlag;								//隕石出現フラグ
	int    random;								//隕石のランダム値
	float speed;

	//静的定数
	static const VECTOR SIZE;					//モデル倍率
	static const float  SPEED;					//移動速度
	static const int    RANDOM_RANGE_X_OR_Y;	//X座標とY座標のランダム座標
	static const float  Z_POSITION;				//Z座標
	static const VECTOR DIR;					//方向
	static const int    RANDOM_ROTATION_SPEED;	//ランダムな回転スピード
	static const float  RADIUS;					//半径の範囲
	static const int    RANGE;					//ランダム値の範囲
};